# serf package manager

[![codecov](https://codecov.io/gh/dk949/serf/branch/trunk/graph/badge.svg?token=VTK1DM5RYI)](https://codecov.io/gh/dk949/serf)
![CMake](https://github.com/dk949/serf/actions/workflows/cmake.yml/badge.svg)

[![C++20](https://img.shields.io/badge/C++-20-blue.svg?style=flat&logo=c%2B%2B)](https://en.cppreference.com/w/cpp/20)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## Basic usage (commands)

### `serf init`

- Initialise current directory.
- This will create a `serf_packages.json` file where serf keeps information
  about repos it needs to get.
- It will also create a `serf_store` directory where the repos actually stored.
- After the repos are cloned into `serf_store`, they will be symlinked to the
  place where the user wishes to actually place the repo.

### `serf init [DIR_NAME]`

- Like `serf init` but will try to initialise directory `[DIR_NAME]`.
- If `[DIR_NAME]` doesn't exist, it will be created.

### `serf clone [REPO_URL]`

- Clones the requested repo into `serf_store`.
  - If command is not executed in the root directory where `serf init` was ran,
    repo will be cloned into the first `serf_store` found in parent directories
    (important for nested serf directories).
  - If no parent directory is initialised as a serf directory, an error is
    thrown.
- A symlink is made to the current directory. Name of the symlink will be the
  same as the name of the repo unless otherwise specified (standard git
  behaviour).
- `[REPO_URL]`, commit hash, branch name and path of the symlink will be
  recorded in `serf_packages.json`.
- An entry is made in `serf_store/.gitignore` to ignore cloned repo and the
  symlink.

### `serf clone [REPO_URL] [PATH]`

- Same as `serf clone [REPO_URL]`, but `[PATH]` specifies where the symlink is
  created (and what it is called).
- If directory does not exist, an error is thrown.
  - E.g. `serf clone https://github.com/dk949/serf_testrepo reponame` will
    create a symlink in project root called `reponame`.
  - E.g.
    `serf clone https://github.com/dk949/serf_testrepo path/to/repo/reponame`
    will create the symlink in `path/to/repo/` (under project root).

### `serf delete [PATH]`

- Removes the symlink, the entry in `serf_packages.json`, the entry in
  `serf_store/.gitignore` and the cloned repo in `serf_store`.
- As if the package was never part of the project.

### `serf checkout [PATH] [BRANCH/TAG/COMMIT]`

- Works like `git checkout`.
- After `[PATH]` is switched to the desired `[BRANCH/TAG/COMMIT]`, this will be
  recorded in `serf_packages.json`.
- If `[PATH]` is switched to a specific branch, the commit hash of the latest
  commit on that branch will be recorded
  - See `serf latest [PATH]` for alternative behaviour.
- This command will not pull any new changes from remote. If desired
  `[BRANCH/TAG/COMMIT]` doe not exist an error will be thrown.

### `serf update`

- Will checkout (and record) the latest commit on the current branch.
- Will perform this operation for all packages.

### `serf update [PATH]`

- Same as `serf checkout latest` but only for specific `[PATH]`.

### `serf latest [PATH]`

- Forces serf always fetch the latest commit from a branch.
  - Not recommended for repos you don't own.
- Commit hash will not be stored, just branch name
- When setting up the project, the latest changes from the branch will be
  pulled.
  - See `serf setup` and `serf`

### `serf pull`

- Pull all remote changes for all packages.
  - Stays on the previously selected commit

### `serf pull [PATH]`

- Same as `serf pull` but only for specific `[PATH]`

### `serf setup`

- Reads the `serf_packages.json` file, clones all necessary repos and switches
  them to correct commit, tag or branch.

### `serf`

- Alias for `serf setup`

## Components

### `serf_packages.json`

- JSON file holding information about installed packages.
  - Also may store any extra global metadata (such as total number of packages).
- Example:

```json
{
  "packages": [
    {
      "branch": null,
      "hash": "5afd95427d06b389b717bc0dfcb7039a6c2a2dbd",
      "path": "path/to/repo/reponame",
      "url": "https://github.com/dk949/serf_testrepo",
      "urlhash": 94241883410560
    },
    {
      "branch": "dev",
      "hash": null,
      "path": "path/to/repo/reponame",
      "url": "https://github.com/dk949/serf_testrepo",
      "urlhash": 98321853470320
    }
  ],
  "numPackages": 2
}

```

- Explanation:
  - All packages are stored in the object `packages`
  - `urlhash` of each package object is the hashed url with the current number
    of packages appended to the end.
    - The number of packages (not counting the one being added) is appended to
      allow multiple versions of the same package (from the same url) to exist.
    - `std::hash<const char*>{}("https://github.com/dk949/serf_testrepo0")`
    - TODO: Consider FNV-1a
  - `branch` refers to the latest commit on a certain branch
    - `dev` in the second example
    - This is enabled by the use of `serf latest [PATH]`
  - `hash` refers to some commit hash (full). It always refers to the same
    version of the repo
    - unless someone does a force push
    - TODO: force push
    - This is the default
  - `hash` and `branch` are mutually exclusive.
    - If both are present or if neither are present, an error is thrown.
  - In the simplest case where repo was cloned into the project root directory
    and not renamed, `path` would have looked like this:
    `"path": "serf_testrepo"`.
    - Because a custom path was specified, the symlink will be created in
      `path/to/repo` and the name of the link will be `reponame`.
  - `url` is self explanatory
    - TODO: support local repos? Probably not.

### `.serf_files`

- In order not to pollute users' project root directories all files relating to
  serf are stored in the folder `.serf_files`
  - Note: on \*nix this is a hidden directory (because of the dot).
  - TODO: figure out how to make a directory hidden on windows.
- This folder can contain the following files/directories. More could be added.
  - `serf_packages.json`
    - File. Holds configurations for all packages.
  - `serf_bin`
    - Directory. Holds the serf binary and any additional scripts that may be
      required in the future.
  - `serf_store`
    - Directory. See below.

### `serf_store`

- This is the directory where all the repositories are actually stored.
- Directory for each repo is named with the same hash as the package (for the
  same reason).
- Symlinks are created in the project directory to the hashed directories.
- Additionally a `.gitignore` file is stored to ignore everything in that
  directory.
  - This is just a file containing `*`

## Todos and oversights

- Windows support, specifically regarding symlinks
- Nested serf project (i.e. cloning a serf project with serf)
- git submodules.
- SSH and authentication

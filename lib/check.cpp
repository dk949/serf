#include "check.hpp"

#include <git2/errors.h>


bool gp::check(git_error_code error) {
    if (error != GIT_OK) {
        const auto *e = git_error_last();
        switch (error) {
            case GIT_OK:                              // all good
                return true;                          //
            case GIT_EEXISTS:                         // already exists
            case GIT_EAPPLIED:                        // patch already applied
            case GIT_ITEROVER:                        // finished iteration
                return false;                         //
                                                      //
            case GIT_ENOTFOUND:                       // coudl not be found
                throw FileNotFound(error, e);         //
            case GIT_EAMBIGUOUS:                      // ambiguous object
                throw AmbiguousObject(error, e);      //
            case GIT_EBUFS:                           // buffer not big enough
                throw BufTooSmall(error, e);          //
            case GIT_EBAREREPO:                       // not allowed in bare repo
                throw NotInBareRepo(error, e);        //
            case GIT_EUSER:                           // user supplied error
                throw UserSuppliedError(error, e);    //
            case GIT_EUNBORNBRANCH:                   // branch has no commits
                throw NoCommitsOnBranch(error, e);    //
            case GIT_EUNMERGED:                       // merge in progress
                throw MergeInProgress(error, e);      //
            case GIT_ENONFASTFORWARD:                 // ref not fast-forwardable
                throw NotFastForwardable(error, e);   //
            case GIT_EINVALIDSPEC:                    // ref or spec invalid format
                throw InvalidSpecFormar(error, e);    //
            case GIT_ECONFLICT:                       // checkout conflict
                throw CheckoutConflict(error, e);     //
            case GIT_ELOCKED:                         // lock file exists
                throw LockFileError(error, e);        //
            case GIT_EMODIFIED:                       // unexpected ref value
                throw UnexpectedRefValue(error, e);   //
            case GIT_EAUTH:                           // authentication
                throw AuthError(error, e);            //
            case GIT_ECERTIFICATE:                    // server certificate invalid
                throw InvalidServerCert(error, e);    //
            case GIT_EPEEL:                           // peel not possible
                throw ImpossiblePeel(error, e);       //
            case GIT_EEOF:                            // Unexpected eof
                throw UnexpectedEOF(error, e);        //
            case GIT_EUNCOMMITTED:                    // uncommiten changes prevent operation
                throw UncommittedChanges(error, e);   //
            case GIT_EDIRECTORY:                      // can not perform on directory
                throw NotFile(error, e);              //
            case GIT_EMERGECONFLICT:                  // merge conflict
                throw MergeConflict(error, e);        //
            case GIT_PASSTHROUGH:                     // callback error
                throw CallbackError(error, e);        //
            case GIT_EMISMATCH:                       // hashsum mismatch
                throw HashMismatch(error, e);         //
            case GIT_EINDEXDIRTY:                     // unsaved changes will be overwritten
                throw UnsavedChangesError(error, e);  //
            case GIT_EAPPLYFAIL:                      // could not apply patch
                throw ApplyFailed(error, e);          //
                                                      //
            case GIT_EINVALID:                        // invalid
            case GIT_ERROR:                           // generic
            case GIT_RETRY:                           // internal use only
            default:                                  // just in case
                throw GitException(error, e);
        }
    }
    return true;
}

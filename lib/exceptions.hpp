#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include "git_exception.hpp"
#define MAKE_EXCEPTION_(X)                 \
    struct X : GitException {             \
        using GitException::GitException; \
    }


namespace gp {
MAKE_EXCEPTION_(FileNotFound);
MAKE_EXCEPTION_(AmbiguousObject);
MAKE_EXCEPTION_(BufTooSmall);
MAKE_EXCEPTION_(NotInBareRepo);
MAKE_EXCEPTION_(UserSuppliedError);
MAKE_EXCEPTION_(NoCommitsOnBranch);
MAKE_EXCEPTION_(MergeInProgress);
MAKE_EXCEPTION_(NotFastForwardable);
MAKE_EXCEPTION_(InvalidSpecFormar);
MAKE_EXCEPTION_(CheckoutConflict);
MAKE_EXCEPTION_(LockFileError);
MAKE_EXCEPTION_(UnexpectedRefValue);
MAKE_EXCEPTION_(AuthError);
MAKE_EXCEPTION_(InvalidServerCert);
MAKE_EXCEPTION_(ImpossiblePeel);
MAKE_EXCEPTION_(UnexpectedEOF);
MAKE_EXCEPTION_(UncommittedChanges);
MAKE_EXCEPTION_(NotFile);
MAKE_EXCEPTION_(MergeConflict);
MAKE_EXCEPTION_(CallbackError);
MAKE_EXCEPTION_(HashMismatch);
MAKE_EXCEPTION_(UnsavedChangesError);
MAKE_EXCEPTION_(ApplyFailed);
}  // namespace gp



#endif  // EXCEPTIONS_HPP

#include "decode_error.hpp"

#include "git2/errors.h"
#define DECODE_ERROR_(X) \
    case (GIT_##X):      \
        return #X

const char *decodeError(git_error_code error) {
    switch (error) {
        DECODE_ERROR_(OK);
        DECODE_ERROR_(ERROR);
        DECODE_ERROR_(ENOTFOUND);
        DECODE_ERROR_(EEXISTS);
        DECODE_ERROR_(EAMBIGUOUS);
        DECODE_ERROR_(EBUFS);
        DECODE_ERROR_(EUSER);
        DECODE_ERROR_(EBAREREPO);
        DECODE_ERROR_(EUNBORNBRANCH);
        DECODE_ERROR_(EUNMERGED);
        DECODE_ERROR_(ENONFASTFORWARD);
        DECODE_ERROR_(EINVALIDSPEC);
        DECODE_ERROR_(ECONFLICT);
        DECODE_ERROR_(ELOCKED);
        DECODE_ERROR_(EMODIFIED);
        DECODE_ERROR_(EAUTH);
        DECODE_ERROR_(ECERTIFICATE);
        DECODE_ERROR_(EAPPLIED);
        DECODE_ERROR_(EPEEL);
        DECODE_ERROR_(EEOF);
        DECODE_ERROR_(EINVALID);
        DECODE_ERROR_(EUNCOMMITTED);
        DECODE_ERROR_(EDIRECTORY);
        DECODE_ERROR_(EMERGECONFLICT);
        DECODE_ERROR_(PASSTHROUGH);
        DECODE_ERROR_(ITEROVER);
        DECODE_ERROR_(RETRY);
        DECODE_ERROR_(EMISMATCH);
        DECODE_ERROR_(EINDEXDIRTY);
        DECODE_ERROR_(EAPPLYFAIL);
    }
    return "UNKNOWN_ERROR";
}

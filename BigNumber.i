%module BigNumber

%include "std_string.i"
%include "std_vector.i"

%{
#include "BigFloat.h"
#include "BigInt.h"
%}
%include "BigFloat.h"
%include "BigInt.h"
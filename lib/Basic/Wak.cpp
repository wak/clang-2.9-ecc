#include "clang/Basic/Wak.h"
#include <cstdio>

using namespace std;

namespace clang {
  void debugPrintEccMarkAttachedToDecl(const ASTContext &Context,
                                       const NamedDecl &D, const char *type) {
    PresumedLoc PLoc = Context.getSourceManager().getPresumedLoc(D.getLocation());
    fprintf(stderr, "wak: ECC attached to %-20s (%s)\t=> %-25s (%s: L.%d, col:%d)\n",
            type, D.getDeclKindName(), D.getNameAsString().c_str(),
            PLoc.getFilename(), PLoc.getLine(), PLoc.getColumn());
  }
}

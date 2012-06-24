#include "clang/Basic/Wak.h"
#include <cstdio>

using namespace std;

namespace clang {
  void debugPrintEccMarkAttachedToDecl(const ASTContext &Context,
                                       const NamedDecl &D, const char *type) {
    PresumedLoc PLoc = Context.getSourceManager().getPresumedLoc(D.getLocation());
    fprintf(stderr, "wak: ECC attached to %-20s (%s)\t=> %-25s (%s: L.%-2d, col:%-2d)\n",
            type, D.getDeclKindName(), D.getNameAsString().c_str(),
            PLoc.getFilename(), PLoc.getLine(), PLoc.getColumn());
  }

  bool VarDecl::isThisTypeEccProtected() const {
    QualType Ty = this->getType();

    if (Ty->isRecordType()) {
      const RecordType *RecordTy = Ty->getAs<RecordType>();
      const RecordDecl *Record = cast<RecordDecl>(RecordTy->getDecl());
      return Record->hasAttr<EccAttr>();
    }
    return false;
  }

  bool VarDecl::doesThisDeclShouldEccProtect() const {
    return hasAttr<EccAttr>() || isThisTypeEccProtected();
  }
}

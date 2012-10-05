#include "clang/Basic/Wak.h"
#include <cstdio>

using namespace std;

namespace clang {
  void debugPrintEccMarkAttachedToDecl(const ASTContext &Context,
                                       const NamedDecl &D, const char *type,
                                       int referenceLevel) {
    PresumedLoc PLoc = Context.getSourceManager().getPresumedLoc(D.getLocation());
    fprintf(stderr, "wak: ECC attached to %-20s (%s)\t=> %-25s (%s: L.%-2d, col:%-2d)",
            type, D.getDeclKindName(), D.getNameAsString().c_str(),
            PLoc.getFilename(), PLoc.getLine(), PLoc.getColumn());
    if (referenceLevel >= 0)
      fprintf(stderr, " RL:%d", referenceLevel);
    fprintf(stderr, "\n");
  }

  bool attachEccMarkToIRIfEccAttrSpecified(llvm::Value *value, const VarDecl &D,
                                           const ASTContext &Context,
                                           const char *type) {
    const EccAttr *eccAttr = D.getEccAttr();
    if (eccAttr == NULL)
      return false;

    int referenceLevel = eccAttr->getReferenceLevel();
    value->isecc = true;
    value->ecc_reference_level = referenceLevel;
    debugPrintEccMarkAttachedToDecl(Context, D, type, referenceLevel);
    return true;
  }

  const EccAttr *getEccAttrFromType(const Type *type) {
    while (type) {
      if (const RecordType *RecordTy = dyn_cast<RecordType>(type)) {
        const RecordDecl *Record = cast<RecordDecl>(RecordTy->getDecl());
        if (Record->hasAttr<EccAttr>())
          return Record->getAttr<EccAttr>();
      }
      if (const TypedefType *TypedefTy = dyn_cast<TypedefType>(type)) {
        const TypedefDecl *Typedef = cast<TypedefDecl>(TypedefTy->getDecl());
        if (Typedef->hasAttr<EccAttr>())
          return Typedef->getAttr<EccAttr>();
        type = Typedef->getTypeSourceInfo()->getType()->getAs<Type>();
        continue;
      }
      break;
    }
    return NULL;
  }

  const EccAttr *VarDecl::getEccAttr() const {
    if (hasAttr<EccAttr>())
      return getAttr<EccAttr>();
    else
      return getEccAttrFromType(this->getType()->getAs<Type>());
  }
}

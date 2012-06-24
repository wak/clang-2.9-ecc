#ifndef LLVM_CLANG_BASIC_WAK_H
#define LLVM_CLANG_BASIC_WAK_H

#include "clang/Basic/SourceLocation.h"
#include "clang/Basic/SourceManager.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"

namespace clang {
  extern void debugPrintEccMarkAttachedToDecl(const ASTContext &Context,
                                              const NamedDecl &D, const char *type);
}

#endif

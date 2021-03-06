set(LLVM_LINK_COMPONENTS support)

set(LLVM_USED_LIBS clangBasic clangLex clangAST clangFrontend clangRewrite)

add_clang_library(clangStaticAnalyzerCore
  AnalysisManager.cpp
  BasicConstraintManager.cpp
  BasicValueFactory.cpp
  BlockCounter.cpp
  BugReporter.cpp
  BugReporterVisitors.cpp
  Checker.cpp
  CheckerContext.cpp
  CheckerHelpers.cpp
  CheckerManager.cpp
  CheckerRegistry.cpp
  CoreEngine.cpp
  Environment.cpp
  ExplodedGraph.cpp
  ExprEngine.cpp
  ExprEngineC.cpp
  ExprEngineCXX.cpp
  ExprEngineCallAndReturn.cpp
  ExprEngineObjC.cpp
  HTMLDiagnostics.cpp
  MemRegion.cpp
  ObjCMessage.cpp
  PathDiagnostic.cpp
  PlistDiagnostics.cpp
  ProgramState.cpp
  RangeConstraintManager.cpp
  RegionStore.cpp
  SValBuilder.cpp
  SVals.cpp
  SimpleConstraintManager.cpp
  SimpleSValBuilder.cpp
  Store.cpp
  SubEngine.cpp
  SymbolManager.cpp
  TextPathDiagnostics.cpp
  )

add_dependencies(clangStaticAnalyzerCore ClangAttrClasses ClangAttrList ClangDeclNodes
                 ClangStmtNodes)

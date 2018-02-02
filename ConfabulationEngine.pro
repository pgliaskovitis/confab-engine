CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O0
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3

QMAKE_CXXFLAGS += -std=c++11

LIBS += -pthread

SOURCES += \
    text_processing/TextReader.cpp \
    text_processing/SentenceTokenizer.cpp \
    text_processing/NGramHandler.cpp \
    ConfabulationTest.cpp \
    Globals.cpp \
    SymbolMapping.cpp \
    KnowledgeBase.cpp \
    Module.cpp \
    MultiLevelOrganizer.cpp \
    ConfabulationBase.cpp \
    ForwardConfabulation.cpp \
    TwoLevelMultiConfabulation.cpp \

HEADERS += \
    sparse_structures/CSRLinksMatrix.hpp \
    sparse_structures/DOKExcitationVector.hpp \
    sparse_structures/IExcitationVector.hpp \
    sparse_structures/IKnowledgeLinks.hpp \
    sparse_structures/DOKLinksMatrix.hpp \
    sparse_structures/SparseHashLinksMatrix.hpp \
    text_processing/TextReader.h \
    text_processing/SentenceTokenizer.h \
    text_processing/NGramHandler.h \
    utils/HashTrie.hpp \
    utils/Utils.h \
    utils/HashTrieNode.hpp \
    ConfabulationTest.h \
    Globals.h \
    SymbolMapping.h \
    KnowledgeBase.h \
    Module.h \
    MultiLevelOrganizer.h \
    ConfabulationBase.h \
    ForwardConfabulation.h \
    Dbg.h \
    TwoLevelMultiConfabulation.h \

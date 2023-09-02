CC := g++
CXXFLAGS := -std=c++14  # 添加你需要的編譯標誌

TARGETS := \
app/Sorting \
app/LinkedList \
app/HashMap \
app/SkipList \
app/BST \
app/AVLTree \
app/RBTree \
app/SplayTree \
app/SpeedTest

# 將所有目標添加到all目標的依賴列表
all: $(TARGETS)

# 定義每個目標的特定源文件
app/Sorting: source/Sorting.cpp
	$(CC) $(CXXFLAGS) $^ -o $@

app/LinkedList: source/LinkedList.cpp
	$(CC) $(CXXFLAGS) $^ -o $@

app/HashMap: source/HashMap.cpp
	$(CC) $(CXXFLAGS) $^ -o $@

app/SkipList: source/SkipList.cpp
	$(CC) $(CXXFLAGS) $^ -o $@

app/BST: source/BST.cpp
	$(CC) $(CXXFLAGS) $^ -o $@

app/AVLTree: source/AVLTree.cpp
	$(CC) $(CXXFLAGS) $^ -o $@

app/RBTree: source/RBTree.cpp
	$(CC) $(CXXFLAGS) $^ -o $@

app/SplayTree: source/SplayTree.cpp
	$(CC) $(CXXFLAGS) $^ -o $@

app/SpeedTest: source/SpeedTest.cpp
	$(CC) $(CXXFLAGS) $^ -o $@

clean: 
	del /Q app\*.exe
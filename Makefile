CC := g++
CXXFLAGS := -std=c++14  # �K�[�A�ݭn���sĶ�лx

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

# �N�Ҧ��ؼвK�[��all�ؼЪ��̿�C��
all: $(TARGETS)

# �w�q�C�ӥؼЪ��S�w�����
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
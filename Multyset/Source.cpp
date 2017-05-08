#include "BinaryTree.h" // Операции над бинарным деревом
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>



using namespace std;

void genTree(BinaryTree<int> &tree, unsigned int quant)
{
	srand(time(NULL));
	for (unsigned int i = 0; i ^ quant; ++i)
	{
		int tmp = rand() % 100;
		cout << "GENERATED " << tmp << endl;
		tree.attach(tmp);
	}
}

void display(int &a)
{
	cout << "&a == " << &a << endl;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	try {
		BinaryTree<int> myTree;
		cout << endl << setw(50) << setfill(' ') << "RED BLACK TREE" << endl;
		cout << "\n 1) Search item.\n 2) Delete item.\n 3) Add item.\n 4) Generate tree.\n 5) Print tree\n 6) Print levels\n\n";

		while (true)
		{
			cout << setw(10) << setfill(' ') << "Select:";
			int a;
			cin >> a;
			switch (a)
			{
			case 1:
			{
				cout << "Element for search:";
				int tmp;
				cin >> tmp;
				if (!myTree.isExist(tmp)) cout << "Not";
				cout << "exist";
				break;
			}
			case 2:
			{
				cout << "Element for delete:";
				int tmp;
				cin >> tmp;
				myTree.deleteItem(tmp);
				break;
			}
			case 3:
			{
				cout << "Element for add:";
				int tmp;
				cin >> tmp;
				myTree.attach(tmp);
				break;
			}
			case 4:
			{
				genTree(myTree, 7);
				break;
			}
			case 5:
			{
				cout << myTree;
				break;
			}
			case 6:
			{
				myTree.printLevels();
				break;
			}

			}
		}

	}
	catch (TreeException error)
	{
		cout << error.what() << endl;
		return 1;
	}
	return 0;
} // Конец функции main
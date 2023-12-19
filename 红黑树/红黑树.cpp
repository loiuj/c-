#include "红黑树.h"

#include <iomanip>

//依次是从父节点，左节点，右节点的深度遍历，用于print输出
void RBTree::putNodeQueue(RBNode* node)
{
	if (node != NULL)
	{
		qRBNode.push(node);
		putNodeQueue(node->left);
		putNodeQueue(node->right);
	}
}

//获取树的深度
int RBTree::getDeepth(RBNode* node)
{
	if (node != NULL)
	{
		int left = getDeepth(node->left);
		int right = getDeepth(node->right);
		return 1 + (left > right ? left : right);
	}
	return 0;
}
//计算不同深度中边界到点的距离
int calcBorderToPoint(int depth)
{
	int tmp = pow(2, depth);
	return (tmp << 1) + tmp - 3;
}

//计算不同深度中点到下一个点的边界的距离
int calcPointToNextBorder(int depth)
{
	return pow(2, depth) * 3 + 1;
}

void PrintSpace(int length)
{
	for (int i = 0; i < length; i++)
		cout << " ";
}

//用于输出一行
//把每个点分为不同区域，每个点为其子节点的中心位置，从下到上建立图像
//但是从下到上会比较困难，所以采取公式从上到下建立
queue<RBNode*>* RBTree::PrintRBNode(queue<RBNode*>* q, int depth)
{
	//用于返回下一层的所有节点，为了下一次输出
	queue<RBNode*>* res = new queue<RBNode*>;
	queue<RBNode*>* print_lean = new queue<RBNode*>(*q);

	//计算需要的数值，这里设定最底层节点间隔4个空格，每个节点两个空格，然后逆推得到了深度对应的数据
	int border_to_point = calcBorderToPoint(depth);
	int point_to_border = calcPointToNextBorder(depth);
	
	
	//判断下一层是否都是NULL节点，不过这里写的时候PrintNode里面就是根据深度决定循环次数的，所以这个flag可以不用
	bool flag = false;
	while (!print_lean->empty())
	{
		RBNode* node = print_lean->front();
		print_lean->pop();
		//为了好看
		if (node == root)
			continue;
		if (node != NULL)
		{
			//打印左边
			PrintSpace(border_to_point);
			scta(0xf0);
			//打印中间
			if (leftOf(parentOf(node)) == node)
				cout << " /";
			else
				cout << "\\ ";
			//打印右边
			PrintSpace(point_to_border);
		}
		else
			//主要为了打印完他所负责的区域
			PrintSpace(border_to_point + 2 + point_to_border);
		
	}
	cout << '\n';
	while (!q->empty())
	{
		RBNode* node = q->front();
		q->pop();
		//如果有的话flag就设置为true
		if (node != NULL)
		{
			flag = true;
			//打印左边
			PrintSpace(border_to_point);
			//打印中间
			if (!node->color)
			{
				scta(0xfc);
				cout << setw(2) << setfill('0') << node->value;
			}
			else
			{
				scta(0xf0);
				cout << setw(2) << setfill('0') << node->value;
			}
			//打印右边
			PrintSpace(point_to_border);
		}
		else
			//主要为了打印完他所负责的区域
			PrintSpace(border_to_point + 2 + point_to_border);
		//用这种方式是为了如果node是null,其也能push进去两个null，为了下一行打印凑东西
		res->push(leftOf(node));
		res->push(rightOf(node));
	}
	cout << endl;
	delete q;
	if (!flag)
	{
		delete res;
		return new queue<RBNode*>;
	}
	return res;
}
//用于第一次输出准备
void RBTree::PrintRBNode(RBNode* node)
{
	//获取深度
	int depth = getDeepth(root);
	queue<RBNode*>* q = new queue<RBNode*>;
	q->push(node);
	while (!q->empty() && depth > 0)
	{
		//为了计算需要就需要减一
		depth--;
		q = PrintRBNode(q, depth);
	}
}

/*
 *围绕p左旋
 *
 *		p				pr
 *	  /  \			   /  \
 *   pl   pr   ==>    p   rr
 *	     /  \        / \
 *		rl  rr      pl  rl
*/
void RBTree::leftRotate(RBNode* p)
{
	if (p == NULL)
	{
		throw "Parameter P is NULL";
	}
	RBNode* r = p->right;
	p->right = r->left;
	if (r->left != NULL)
		r->left->parent = p;
	r->parent = p->parent;
	if (p->parent == NULL)
		root = r;
	else if (p->parent->left == p)
		p->parent->left = r;
	else
		p->parent->right = r;
	r->left = p;
	p->parent = r;
}

/*
 *围绕右旋
 *
 *		p				pl
 *	  /  \			   /  \
 *   pl   pr   ==>    ll   p
 *	/  \				  / \
 * ll	lr				 lr	 pr
*/
void RBTree::rightRotate(RBNode* p)
{
	if (p == NULL)
	{
		throw "Parameter P is NULL";
		return;
	}
	RBNode* l = p->left;
	p->left = l->right;
	if (l->right != NULL)
		l->right->parent = p;
	l->parent = p->parent;
	if (p->parent == NULL)
		root = l;
	else if (p->parent->left == p)
		p->parent->left = l;
	else
		p->parent->right = l;
	l->right = p;
	p->parent = l;
}

//k1小为True,否则为false
bool RBTree::compare(int k1, int k2)
{
	return k1 < k2;
}
//闲得打那么多
RBNode* RBTree::createRBNode(int key, int value)
{
	return new RBNode(key, value, Red, NULL, NULL, NULL);
}
RBNode* RBTree::createRBNode(int key, int value, color color)
{
	return new RBNode(key, value, color, NULL, NULL, NULL);
}
RBNode* RBTree::createRBNode(int key, int value, RBNode* left, RBNode* right)
{
	return new RBNode(key, value, Red, left, right, NULL);
}
RBNode* RBTree::createRBNode(int key, int value, RBNode* parent)
{
	return new RBNode(key, value, Red, NULL, NULL, parent);
}
RBNode* RBTree::createRBNode(int key, int value, RBNode* left, RBNode* right, RBNode* parent)
{
	return new RBNode(key, value, Red, left, right, parent);
}

//调整节点
void RBTree::fixAfterPut(RBNode* node)
{
	//父节点不是黑色才要判断，其他都是直接加不调整
	while (node != NULL && node != root && node->parent->color != Black)
	{
		//1.x的父节点是爷爷的左孩子(左3)
		if (parentOf(node) == leftOf(parentOf(parentOf(node))))
		{
			//叔叔节点
			RBNode* y = rightOf(parentOf(parentOf(node)));
			//第三种情况
			if (colorOf(y) == Red)
			{
				setColor(parentOf(node), Black);
				setColor(y, Black);
				setColor(parentOf(parentOf(node)), Red);
				//从下到上，会去递归得遍历
				node = parentOf(parentOf(node));
			}
			//第二种清空
			//这里的Black指的是NULL
			else
			{
				//如果Node是右节点，则要先根据父节点左旋在一条线
				if (rightOf(parentOf(node)) == node)
				{
					node = parentOf(node);
					leftRotate(node);
				}

				//父亲变黑
				setColor(parentOf(node), Black);
				//爷爷变红
				setColor(parentOf(parentOf(node)), Red);
				//根据爷爷节点右旋
				rightRotate(parentOf(parentOf(node)));
			}
		}
		//右边第三种清空
		else
		{
			//叔叔节点
			RBNode* y = leftOf(parentOf(parentOf(node)));
			//第三种情况
			if (colorOf(y) == Red)
			{
				setColor(parentOf(node), Black);
				setColor(y, Black);
				setColor(parentOf(parentOf(node)), Red);
				node = parentOf(parentOf(node));
			}
			//2.跟第一种清空相反操作
			//这里的Black指的是NULL
			else
			{
				//如果Node是左节点，则要先根据父节点左旋在一条线
				if (leftOf(parentOf(node)) == node)
				{
					node = parentOf(node);
					rightRotate(node);
				}

				//父亲变黑
				setColor(parentOf(node), Black);
				//爷爷变红
				setColor(parentOf(parentOf(node)), Red);
				//根据爷爷节点右旋
				leftRotate(parentOf(parentOf(node)));
			}
		}
	}
	//重置root颜色
	root->color = Black;
}

//便于调试的插入
void RBTree::push(int k)
{
	push(k, k);
}

//插入节点
void RBTree::push(int k, int value)
{
	RBNode* t = this->root;
	//如果根节点
	if (t == NULL)
	{
		root = createRBNode(k, value, Black);
		return;
	}
	RBNode* parent = NULL;
	//寻找插入位置
	//这一段等模板化后再插入，不然0就是NULL会抛出异常的
	//if (k == NULL)
	//	throw "key is NULL in push";
	while (t)
	{
		parent = t;
		if (t->key == k)
		{
			t->value = value;
			return;
		}
		else if (compare(k, t->value))
		{
			t = t->left;
		}
		else
		{
			t = t->right;
		}
	}
	RBNode* nNode = createRBNode(k, value, parent);
	//如果k<value,放在左边
	if (compare(k, parent->value))
		parent->left = nNode;
	else
		parent->right = nNode;
	fixAfterPut(nNode);
}

//获取前驱节点
RBNode* RBTree::predecessor(RBNode* node)
{
	if (node == NULL)
		return NULL;
	else if (node->left != NULL)
	{
		RBNode* p = node->left;
		while (p->right != NULL)
			p = p->right;
		return p;
	}
	else
	{
		RBNode* p = node;
		while (leftOf(parentOf(p)) == p)
		{
			p = p->parent;
		}
		return p;
	}
}

//获取后继节点
RBNode* RBTree::sucessor(RBNode* node)
{
	if (node == NULL)
		return NULL;
	else if (node->right != NULL)
	{
		RBNode* p = node->right;
		while (p->left != NULL)
			p = p->left;
		return p;
	}
	else
	{
		//如果右边没有节点，则后继会在他的父亲上
		RBNode* p = node;
		while (rightOf(parentOf(p)) == p)
		{
			p = p->parent;
		}
		return p;
	}
}

//获取节点
RBNode* RBTree::getNode(int key)
{
	RBNode* node = root;
	//不等于NULL
	while (node)
		if (compare(key, node->key))
			node = node->left;
	//防止模板化后没有重载key的==操作
		else if (compare(node->key, key))
			node = node->right;
		else
			return node;
	return node;
}

//删除后修改节点
void RBTree::fixAfterRemove(RBNode* node)
{
	//if里面就是自己不能解决，得找兄弟或者父亲借的情况
	while(node != root && colorOf(node) == Black)
	{
		//node是左孩子情况
		if (node == leftOf(parentOf(node)))
		{
			RBNode* rNode = rightOf(parentOf(node));

			//判断此时兄弟节点是否是真正的兄弟节点
			//判断其是否是红色，是的话左旋
			//不知道这样然后直接rNode=左边的黑色节点，后续要和父节点结合，如果旋转的话对父节点进行操作会比较困难
			if(!colorOf(rNode))
			{
				setColor(rNode, Black);
				setColor(parentOf(node), Red);
				leftRotate(parentOf(node));
				rNode = rightOf(parentOf(node));
			}
			//情况三，兄弟没得借
			//这个其实colorOF本质是判断是否为null,emmmm
			//个人认为应该是判断如果是红色才代表是他的孩子，则兄弟有的借，如果是黑色那又是其他分支了，所以才要判断是否是黑色
			//我的设置里面black等于true,所以就这样了
			if (colorOf(leftOf(rNode)) && colorOf(rightOf(rNode)))
			{
				setColor(rNode, Red);
				node = parentOf(node);

			}
			//情况二 ，兄弟有的借
			else
			{
				//分两种小情况，兄弟本来是3节点或者四节点的情况
				//三节点情况
				//因为只有rNode!=NULL上面才能通过返回Red，所以个人认为应该也能直接->
				if(rNode->right == NULL)
				{
					//右旋把右边小的节点变为兄弟，作为借的节点
					setColor(rNode->left, Black);
					setColor(rNode, Red);
					rightRotate(rNode);
					rNode = rightOf(parentOf(node));
				}
				//因为上面已经调整过了，所以三种情况变成了两种情况
				//一个是只有右孩子，直接左旋一次就行
				//还有一个是有两个孩子，也可以直接左旋一次，相当于一次借两个节点
				setColor(rNode, colorOf(parentOf(node)));//父节点可能黑色，所以需要变成黑色，例如父节点是根节点
				setColor(parentOf(node), Black);
				setColor(rightOf(rNode), Black);
				leftRotate(parentOf(node));
				//为了结束循环，作者思路是递归到根，因为后面与兄弟父节点合并操作
				node = root;
			}

		}
		//node是右孩子情况
		else
		{
			RBNode* rNode = leftOf(parentOf(node));

			//判断此时兄弟节点是否是真正的兄弟节点
			//判断其是否是红色，是的话左旋
			//不知道这样然后直接rNode=左边的黑色节点，后续要和父节点结合，如果旋转的话对父节点进行操作会比较困难
			if (!colorOf(rNode))
			{
				setColor(rNode, Black);
				setColor(parentOf(node), Red);
				rightRotate(parentOf(node));
				rNode = leftOf(parentOf(node));
			}
			//情况三，兄弟没得借
			//这个其实colorOF本质是判断是否为null,emmmm
			//个人认为应该是判断如果是红色才代表是他的孩子，则兄弟有的借，如果是黑色那又是其他分支了，所以才要判断是否是黑色
			//我的设置里面black等于true,所以就这样了
			if (colorOf(leftOf(rNode)) && colorOf(rightOf(rNode)))
			{
				setColor(rNode, Red);
				node = parentOf(node);

			}
			//情况二 ，兄弟有的借
			else
			{
				//分两种小情况，兄弟本来是3节点或者四节点的情况
				//三节点情况
				//因为只有rNode!=NULL上面才能通过返回Red，所以个人认为应该也能直接->
				if (rNode->left == NULL)
				{
					//左旋把右边小的节点变为兄弟，作为借的节点
					setColor(rNode->right, Black);
					setColor(rNode, Red);
					leftRotate(rNode);
					rNode = leftOf(parentOf(node));
				}
				//因为上面已经调整过了，所以三种情况变成了两种情况
				//一个是只有左孩子，直接左旋一次就行
				//还有一个是有两个孩子，也可以直接右旋一次，相当于一次借两个节点
				setColor(rNode, colorOf(parentOf(node)));//父节点可能黑色，所以需要变成黑色，例如父节点是根节点
				setColor(parentOf(node), Black);
				setColor(leftOf(rNode), Black);
				rightRotate(parentOf(node));
				//为了结束循环，作者思路是递归到根，因为后面与兄弟父节点合并操作
				node = root;
			}

		}

	}
	//替代节点是红色，直接染红，补偿删除的黑色节点，这样红黑树依然保持平衡
	setColor(node, Black);
}


//删除节点
void RBTree::deleteNode(RBNode* node)
{
	//3.节点有两个孩子
	//传入的时候就是非NULL了，没有问题
	if (node->left != NULL && node->right != NULL)
	{
		RBNode* s_node = sucessor(node);
		node->key = s_node->key;
		node->value = s_node->value;
		node = s_node;
	}
	RBNode* replacement = node->left != NULL ? node->left : node->right;
	//替代节点不为空
	if (replacement != NULL)
	{
		//替代者的父节点指向原来node的父亲
		replacement->parent = node->parent;
		if (node->parent == NULL)
			root = replacement;
		else if (node == node->parent->left)
			node->parent->left = replacement;
		else
			node->parent->right = replacement;


		//替换之后要调整平衡
		//这里属于node是3节点，所以可以直接子节点改色完成修改
		if (node->color == Black)
		{
			//需要调整
			//这种情况一定是替代节点一定是红色，换成黑色
			//第二种情况，就是自己有一个子节点可以自己解决掉删除，所以调用修改，但其实也可以自己去改颜色，只不过是为了复用性更高，可能
			fixAfterRemove(replacement);
		}
		//回收node节点，因为上面还要使用，所以这样回收
		delete node;
	}
	//删除节点就是根节点
	else if (node->parent == NULL)
	{
		root = NULL;
		delete node;
	}
	//叶子节点,replacement为null
	else
	{
		//先调整
		//这里如果要是replacement == null则说明为第一种情况，就是删除节点就是红色节点，所以可以直接删除，不处理
		if (node->color == Black)
		{
			fixAfterRemove(node);
		}
		//调整后可能会导致不是父节点了
		if (node->parent != NULL)
		{
			if (node == node->parent->left)
				node->parent->left = NULL;
			else
				node->parent->right = NULL;
		}
		delete node;
	}
}

//删除节点的同时返回该节点数据
int RBTree::remove(int key)
{
	RBNode* node = getNode(key);
	if (node == NULL)
		return NULL;
	int old_value = node->value;
	deleteNode(node);
	return old_value;
}

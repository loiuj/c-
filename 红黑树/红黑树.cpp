#include "�����.h"

#include <iomanip>

//�����ǴӸ��ڵ㣬��ڵ㣬�ҽڵ����ȱ���������print���
void RBTree::putNodeQueue(RBNode* node)
{
	if (node != NULL)
	{
		qRBNode.push(node);
		putNodeQueue(node->left);
		putNodeQueue(node->right);
	}
}

//��ȡ�������
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
//���㲻ͬ����б߽絽��ľ���
int calcBorderToPoint(int depth)
{
	int tmp = pow(2, depth);
	return (tmp << 1) + tmp - 3;
}

//���㲻ͬ����е㵽��һ����ı߽�ľ���
int calcPointToNextBorder(int depth)
{
	return pow(2, depth) * 3 + 1;
}

void PrintSpace(int length)
{
	for (int i = 0; i < length; i++)
		cout << " ";
}

//�������һ��
//��ÿ�����Ϊ��ͬ����ÿ����Ϊ���ӽڵ������λ�ã����µ��Ͻ���ͼ��
//���Ǵ��µ��ϻ�Ƚ����ѣ����Բ�ȡ��ʽ���ϵ��½���
queue<RBNode*>* RBTree::PrintRBNode(queue<RBNode*>* q, int depth)
{
	//���ڷ�����һ������нڵ㣬Ϊ����һ�����
	queue<RBNode*>* res = new queue<RBNode*>;
	queue<RBNode*>* print_lean = new queue<RBNode*>(*q);

	//������Ҫ����ֵ�������趨��ײ�ڵ���4���ո�ÿ���ڵ������ո�Ȼ�����Ƶõ�����ȶ�Ӧ������
	int border_to_point = calcBorderToPoint(depth);
	int point_to_border = calcPointToNextBorder(depth);
	
	
	//�ж���һ���Ƿ���NULL�ڵ㣬��������д��ʱ��PrintNode������Ǹ�����Ⱦ���ѭ�������ģ��������flag���Բ���
	bool flag = false;
	while (!print_lean->empty())
	{
		RBNode* node = print_lean->front();
		print_lean->pop();
		//Ϊ�˺ÿ�
		if (node == root)
			continue;
		if (node != NULL)
		{
			//��ӡ���
			PrintSpace(border_to_point);
			scta(0xf0);
			//��ӡ�м�
			if (leftOf(parentOf(node)) == node)
				cout << " /";
			else
				cout << "\\ ";
			//��ӡ�ұ�
			PrintSpace(point_to_border);
		}
		else
			//��ҪΪ�˴�ӡ���������������
			PrintSpace(border_to_point + 2 + point_to_border);
		
	}
	cout << '\n';
	while (!q->empty())
	{
		RBNode* node = q->front();
		q->pop();
		//����еĻ�flag������Ϊtrue
		if (node != NULL)
		{
			flag = true;
			//��ӡ���
			PrintSpace(border_to_point);
			//��ӡ�м�
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
			//��ӡ�ұ�
			PrintSpace(point_to_border);
		}
		else
			//��ҪΪ�˴�ӡ���������������
			PrintSpace(border_to_point + 2 + point_to_border);
		//�����ַ�ʽ��Ϊ�����node��null,��Ҳ��push��ȥ����null��Ϊ����һ�д�ӡ�ն���
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
//���ڵ�һ�����׼��
void RBTree::PrintRBNode(RBNode* node)
{
	//��ȡ���
	int depth = getDeepth(root);
	queue<RBNode*>* q = new queue<RBNode*>;
	q->push(node);
	while (!q->empty() && depth > 0)
	{
		//Ϊ�˼�����Ҫ����Ҫ��һ
		depth--;
		q = PrintRBNode(q, depth);
	}
}

/*
 *Χ��p����
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
 *Χ������
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

//k1СΪTrue,����Ϊfalse
bool RBTree::compare(int k1, int k2)
{
	return k1 < k2;
}
//�еô���ô��
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

//�����ڵ�
void RBTree::fixAfterPut(RBNode* node)
{
	//���ڵ㲻�Ǻ�ɫ��Ҫ�жϣ���������ֱ�ӼӲ�����
	while (node != NULL && node != root && node->parent->color != Black)
	{
		//1.x�ĸ��ڵ���үү������(��3)
		if (parentOf(node) == leftOf(parentOf(parentOf(node))))
		{
			//����ڵ�
			RBNode* y = rightOf(parentOf(parentOf(node)));
			//���������
			if (colorOf(y) == Red)
			{
				setColor(parentOf(node), Black);
				setColor(y, Black);
				setColor(parentOf(parentOf(node)), Red);
				//���µ��ϣ���ȥ�ݹ�ñ���
				node = parentOf(parentOf(node));
			}
			//�ڶ������
			//�����Blackָ����NULL
			else
			{
				//���Node���ҽڵ㣬��Ҫ�ȸ��ݸ��ڵ�������һ����
				if (rightOf(parentOf(node)) == node)
				{
					node = parentOf(node);
					leftRotate(node);
				}

				//���ױ��
				setColor(parentOf(node), Black);
				//үү���
				setColor(parentOf(parentOf(node)), Red);
				//����үү�ڵ�����
				rightRotate(parentOf(parentOf(node)));
			}
		}
		//�ұߵ��������
		else
		{
			//����ڵ�
			RBNode* y = leftOf(parentOf(parentOf(node)));
			//���������
			if (colorOf(y) == Red)
			{
				setColor(parentOf(node), Black);
				setColor(y, Black);
				setColor(parentOf(parentOf(node)), Red);
				node = parentOf(parentOf(node));
			}
			//2.����һ������෴����
			//�����Blackָ����NULL
			else
			{
				//���Node����ڵ㣬��Ҫ�ȸ��ݸ��ڵ�������һ����
				if (leftOf(parentOf(node)) == node)
				{
					node = parentOf(node);
					rightRotate(node);
				}

				//���ױ��
				setColor(parentOf(node), Black);
				//үү���
				setColor(parentOf(parentOf(node)), Red);
				//����үү�ڵ�����
				leftRotate(parentOf(parentOf(node)));
			}
		}
	}
	//����root��ɫ
	root->color = Black;
}

//���ڵ��ԵĲ���
void RBTree::push(int k)
{
	push(k, k);
}

//����ڵ�
void RBTree::push(int k, int value)
{
	RBNode* t = this->root;
	//������ڵ�
	if (t == NULL)
	{
		root = createRBNode(k, value, Black);
		return;
	}
	RBNode* parent = NULL;
	//Ѱ�Ҳ���λ��
	//��һ�ε�ģ�廯���ٲ��룬��Ȼ0����NULL���׳��쳣��
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
	//���k<value,�������
	if (compare(k, parent->value))
		parent->left = nNode;
	else
		parent->right = nNode;
	fixAfterPut(nNode);
}

//��ȡǰ���ڵ�
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

//��ȡ��̽ڵ�
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
		//����ұ�û�нڵ㣬���̻������ĸ�����
		RBNode* p = node;
		while (rightOf(parentOf(p)) == p)
		{
			p = p->parent;
		}
		return p;
	}
}

//��ȡ�ڵ�
RBNode* RBTree::getNode(int key)
{
	RBNode* node = root;
	//������NULL
	while (node)
		if (compare(key, node->key))
			node = node->left;
	//��ֹģ�廯��û������key��==����
		else if (compare(node->key, key))
			node = node->right;
		else
			return node;
	return node;
}

//ɾ�����޸Ľڵ�
void RBTree::fixAfterRemove(RBNode* node)
{
	//if��������Լ����ܽ���������ֵܻ��߸��׽�����
	while(node != root && colorOf(node) == Black)
	{
		//node���������
		if (node == leftOf(parentOf(node)))
		{
			RBNode* rNode = rightOf(parentOf(node));

			//�жϴ�ʱ�ֵܽڵ��Ƿ����������ֵܽڵ�
			//�ж����Ƿ��Ǻ�ɫ���ǵĻ�����
			//��֪������Ȼ��ֱ��rNode=��ߵĺ�ɫ�ڵ㣬����Ҫ�͸��ڵ��ϣ������ת�Ļ��Ը��ڵ���в�����Ƚ�����
			if(!colorOf(rNode))
			{
				setColor(rNode, Black);
				setColor(parentOf(node), Red);
				leftRotate(parentOf(node));
				rNode = rightOf(parentOf(node));
			}
			//��������ֵ�û�ý�
			//�����ʵcolorOF�������ж��Ƿ�Ϊnull,emmmm
			//������ΪӦ�����ж�����Ǻ�ɫ�Ŵ��������ĺ��ӣ����ֵ��еĽ裬����Ǻ�ɫ������������֧�ˣ����Բ�Ҫ�ж��Ƿ��Ǻ�ɫ
			//�ҵ���������black����true,���Ծ�������
			if (colorOf(leftOf(rNode)) && colorOf(rightOf(rNode)))
			{
				setColor(rNode, Red);
				node = parentOf(node);

			}
			//����� ���ֵ��еĽ�
			else
			{
				//������С������ֵܱ�����3�ڵ�����Ľڵ�����
				//���ڵ����
				//��Ϊֻ��rNode!=NULL�������ͨ������Red�����Ը�����ΪӦ��Ҳ��ֱ��->
				if(rNode->right == NULL)
				{
					//�������ұ�С�Ľڵ��Ϊ�ֵܣ���Ϊ��Ľڵ�
					setColor(rNode->left, Black);
					setColor(rNode, Red);
					rightRotate(rNode);
					rNode = rightOf(parentOf(node));
				}
				//��Ϊ�����Ѿ��������ˣ������������������������
				//һ����ֻ���Һ��ӣ�ֱ������һ�ξ���
				//����һ�������������ӣ�Ҳ����ֱ������һ�Σ��൱��һ�ν������ڵ�
				setColor(rNode, colorOf(parentOf(node)));//���ڵ���ܺ�ɫ��������Ҫ��ɺ�ɫ�����縸�ڵ��Ǹ��ڵ�
				setColor(parentOf(node), Black);
				setColor(rightOf(rNode), Black);
				leftRotate(parentOf(node));
				//Ϊ�˽���ѭ��������˼·�ǵݹ鵽������Ϊ�������ֵܸ��ڵ�ϲ�����
				node = root;
			}

		}
		//node���Һ������
		else
		{
			RBNode* rNode = leftOf(parentOf(node));

			//�жϴ�ʱ�ֵܽڵ��Ƿ����������ֵܽڵ�
			//�ж����Ƿ��Ǻ�ɫ���ǵĻ�����
			//��֪������Ȼ��ֱ��rNode=��ߵĺ�ɫ�ڵ㣬����Ҫ�͸��ڵ��ϣ������ת�Ļ��Ը��ڵ���в�����Ƚ�����
			if (!colorOf(rNode))
			{
				setColor(rNode, Black);
				setColor(parentOf(node), Red);
				rightRotate(parentOf(node));
				rNode = leftOf(parentOf(node));
			}
			//��������ֵ�û�ý�
			//�����ʵcolorOF�������ж��Ƿ�Ϊnull,emmmm
			//������ΪӦ�����ж�����Ǻ�ɫ�Ŵ��������ĺ��ӣ����ֵ��еĽ裬����Ǻ�ɫ������������֧�ˣ����Բ�Ҫ�ж��Ƿ��Ǻ�ɫ
			//�ҵ���������black����true,���Ծ�������
			if (colorOf(leftOf(rNode)) && colorOf(rightOf(rNode)))
			{
				setColor(rNode, Red);
				node = parentOf(node);

			}
			//����� ���ֵ��еĽ�
			else
			{
				//������С������ֵܱ�����3�ڵ�����Ľڵ�����
				//���ڵ����
				//��Ϊֻ��rNode!=NULL�������ͨ������Red�����Ը�����ΪӦ��Ҳ��ֱ��->
				if (rNode->left == NULL)
				{
					//�������ұ�С�Ľڵ��Ϊ�ֵܣ���Ϊ��Ľڵ�
					setColor(rNode->right, Black);
					setColor(rNode, Red);
					leftRotate(rNode);
					rNode = leftOf(parentOf(node));
				}
				//��Ϊ�����Ѿ��������ˣ������������������������
				//һ����ֻ�����ӣ�ֱ������һ�ξ���
				//����һ�������������ӣ�Ҳ����ֱ������һ�Σ��൱��һ�ν������ڵ�
				setColor(rNode, colorOf(parentOf(node)));//���ڵ���ܺ�ɫ��������Ҫ��ɺ�ɫ�����縸�ڵ��Ǹ��ڵ�
				setColor(parentOf(node), Black);
				setColor(leftOf(rNode), Black);
				rightRotate(parentOf(node));
				//Ϊ�˽���ѭ��������˼·�ǵݹ鵽������Ϊ�������ֵܸ��ڵ�ϲ�����
				node = root;
			}

		}

	}
	//����ڵ��Ǻ�ɫ��ֱ��Ⱦ�죬����ɾ���ĺ�ɫ�ڵ㣬�����������Ȼ����ƽ��
	setColor(node, Black);
}


//ɾ���ڵ�
void RBTree::deleteNode(RBNode* node)
{
	//3.�ڵ�����������
	//�����ʱ����Ƿ�NULL�ˣ�û������
	if (node->left != NULL && node->right != NULL)
	{
		RBNode* s_node = sucessor(node);
		node->key = s_node->key;
		node->value = s_node->value;
		node = s_node;
	}
	RBNode* replacement = node->left != NULL ? node->left : node->right;
	//����ڵ㲻Ϊ��
	if (replacement != NULL)
	{
		//����ߵĸ��ڵ�ָ��ԭ��node�ĸ���
		replacement->parent = node->parent;
		if (node->parent == NULL)
			root = replacement;
		else if (node == node->parent->left)
			node->parent->left = replacement;
		else
			node->parent->right = replacement;


		//�滻֮��Ҫ����ƽ��
		//��������node��3�ڵ㣬���Կ���ֱ���ӽڵ��ɫ����޸�
		if (node->color == Black)
		{
			//��Ҫ����
			//�������һ��������ڵ�һ���Ǻ�ɫ�����ɺ�ɫ
			//�ڶ�������������Լ���һ���ӽڵ�����Լ������ɾ�������Ե����޸ģ�����ʵҲ�����Լ�ȥ����ɫ��ֻ������Ϊ�˸����Ը��ߣ�����
			fixAfterRemove(replacement);
		}
		//����node�ڵ㣬��Ϊ���滹Ҫʹ�ã�������������
		delete node;
	}
	//ɾ���ڵ���Ǹ��ڵ�
	else if (node->parent == NULL)
	{
		root = NULL;
		delete node;
	}
	//Ҷ�ӽڵ�,replacementΪnull
	else
	{
		//�ȵ���
		//�������Ҫ��replacement == null��˵��Ϊ��һ�����������ɾ���ڵ���Ǻ�ɫ�ڵ㣬���Կ���ֱ��ɾ����������
		if (node->color == Black)
		{
			fixAfterRemove(node);
		}
		//��������ܻᵼ�²��Ǹ��ڵ���
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

//ɾ���ڵ��ͬʱ���ظýڵ�����
int RBTree::remove(int key)
{
	RBNode* node = getNode(key);
	if (node == NULL)
		return NULL;
	int old_value = node->value;
	deleteNode(node);
	return old_value;
}

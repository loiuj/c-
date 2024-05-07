#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "sort_type.h"
using namespace std;
#include "compare.h"

#include <queue>
enum
{
	read_len = 4,
	write_len = 4,
	wrap_len = 4
};
//当前行数,只是为了输出好看
int now_write_len;
//判断数据是否读完
bool text_complited = false;
//数据行数
int Text_lines;
//读的文件
string read_txt_name;
//写的文件
string write_txt_name;

//当前块顺序的长度
int sorted_line_len;
//当前完成排序的行
int complited_sort_line;
//当前被排序的行
int now_sorted_line;

void WriteText(int* array, int len)
{
	fstream fs;
	fs.open(write_txt_name, ios::out | ios::app);
	for (int i = 0; i < len; i++)
	{
		fs << array[i] << " ";
		if (++now_write_len >= wrap_len)
		{
			fs << '\n';
			now_write_len = 0;
		}
	}
	fs.close();
}

void FormatText()
{
	ifstream ifs;
	ifs.open("text.txt", ios::in);
	char c;
	string str_num;
	int i = 0;
	Text_lines = 0;
	int* array = new int[read_len];
	while (true)
	{
		while (i < read_len && (c = ifs.get()) != EOF)
		{
			if (c != ' ' and c != '\n')
			{
				str_num += c;
				continue;
			}
			array[i] = stoi(str_num);
			i++;
			str_num = "";
		}
		//进行排序，讲每一个小块处理成一个有序的
		BubbleSort(array, i, Compare);
		WriteText(array, i);
		i = 0;
		Text_lines++;
		if (c == EOF)
		{
			ifs.close();
			return;
		}

	}

}

//负责模拟从磁盘中分块读取数据，然后放入传入的队列中，如果文件中没有数据或者打开失败了返回false
bool ReadText(queue<int>& p, int line)
{
	ifstream ifs;
	ifs.open(read_txt_name, ios::in);
	assert(ifs.is_open());
	string buff;

	int i = line;

	while (i)
	{
		if (!getline(ifs, buff))
			return false;
		i--;
	}

	string str_num = "";
	for (i = 0; i < buff.length(); i++)
	{
		if (buff[i] != ' ' and buff[i] != '\n')
		{
			str_num += buff[i];
			continue;
		}
		p.push(stoi(str_num));
		str_num = "";
	}
	return true;
}

class Gamer
{
public:
	Gamer()
	{
		if (now_sorted_line >= Text_lines)
		{
			has_data_ = false;
			text_complited = true;
		}
		else
		{
			read_line_ = now_sorted_line + 1;
			start_line_ = read_line_;
			has_data_ = ReadText(p_, read_line_);
			index_ = gamer_index_now_;
			gamer_index_now_++;
			now_sorted_line += sorted_line_len;
		}


	}
	Gamer(bool)//作为一个特殊的存在
	{
		has_data_ = false;
	}
	void PrintGamer()
	{
		cout << index_ << ": " << has_data_ << "  ";
		if (has_data_)
			cout << front();
		cout << endl;
	}

	//返回队头元素
	int front()
	{
		assert(has_data_);
		return p_.front();

	}

	int pop()
	{
		assert(has_data_);
		int data = p_.front();
		p_.pop();
		AddData();
		return data;
	}

	bool HasData()
	{
		return has_data_;
	}
	static void SetIndex(int start)
	{
		gamer_index_now_ = start;
	}
	int GetIndex()
	{
		return index_;
	}
private:
	void AddData()
	{
		if (p_.empty())
		{
			read_line_++;
			if (read_line_ < start_line_ + sorted_line_len)
			{
				has_data_ = ReadText(p_, read_line_);
				return;
			}
			has_data_ = false;
		}

	}
	//记得一个里面取完后要让他自己加上一个无穷大的数字
	bool has_data_;
	queue<int> p_;
	static int gamer_index_now_;
	int index_;
	int read_line_;
	int start_line_;
};
int Gamer::gamer_index_now_;

class LoserTree
{
public:
	LoserTree(int gamer_count)
	{
		Gamer(true).SetIndex(gamer_count);
		gamers_count_ = gamer_count * 2;
		gamers_ = new Gamer * [gamer_count * 2];
		int i = 0;
		for (i = 0; i < gamer_count; i++)
			gamers_[i] = NULL;
		for (i = gamer_count; i < gamers_count_; i++)
			gamers_[i] = new Gamer();
		InitialTree();
	}

	void PopFront()
	{
		int index;
		if (gamers_[0]->HasData())
		{
			index = gamers_[0]->GetIndex();
			gamers_[0]->pop();
			gamers_[0] = NULL;//把这个位置空出来
			Competition(index);
		}
		else
		{
			index = gamers_count_ / 2;
			while (!gamers_[index]->HasData())
			{
				if (++index >= gamers_count_)
				{
					gamers_[0] = NULL;
					return;
				}
			}
			gamers_[0] = NULL;
			Competition(index);
		}
	}

	void Competition(int gamer_index)
	{
		if (gamers_[gamer_index] != NULL)//确保参赛者不是NULL
		{
			//定义当前参赛者
			Gamer* self = gamers_[gamer_index];
			//第一次比较的时候和父节点比较
			int rival = gamer_index / 2;
			//如果父节点是空的，那么他自己就占掉这个位置
			//0号这个位置不会有人占用的，因为顶不上去
			while (gamers_[rival] != NULL && rival)
			{
				//因为我们从大到小排序，所以如果自己比父节点大，则自己占掉这个位置
				//特殊情况，如果其没有数据，则这个地方被他占用
				//如果这个地方没有数据，默认其为最大值，我们自动跳过这个位置
				if (gamers_[rival]->HasData() && (!self->HasData() || self->front() > gamers_[rival]->front()))
				{
					Gamer* tmp = self;
					self = gamers_[rival];
					gamers_[rival] = tmp;
				}
				rival = rival / 2;//让他每次和自己的父节点比较
			}
			gamers_[rival] = self;
			cout << rival << ": ";
			gamers_[rival]->PrintGamer();
		}
	}

	void PrintGamers() const
	{
		for (int i = 0; i < gamers_count_; i++)
		{
			cout << i << ":  ";
			if (gamers_[i] == NULL)
				cout << "NULL" << endl;
			else
				gamers_[i]->PrintGamer();
		}
	}

	int GetWin()
	{
		assert(!empty());
		return gamers_[0]->front();
	}
	bool empty()
	{
		return !gamers_[0]->HasData();
	}
	~LoserTree()
	{
		delete[]gamers_;
	}
private:
	void InitialTree()
	{
		if ((gamers_count_ / 2) % 2)
			gamers_[gamers_count_] = new Gamer(true);
		for (int i = gamers_count_ - 1; i >= gamers_count_ / 2; i--)
			Competition(i);
	}
	Gamer** gamers_;
	int gamers_count_;
};

void PrintList(int* array, int len)
{
	for (int i = 0; i < len; i++)
		cout << array[i] << "  ";
	cout << endl;
}

void SwapWriteAndRead()
{
	string tmp = write_txt_name;
	write_txt_name = read_txt_name;
	read_txt_name = tmp;
}

void ClearText(string text)
{
	ofstream ofs;
	ofs.open(text, ios::in | ios::trunc);
	ofs.close();
}

void CopyText(string input_text, string output_text)
{
	ifstream ifs;
	ofstream ofs;
	ifs.open(input_text, ios::in);
	ofs.open(output_text, ios::trunc);
	char c;
	while ((c = ifs.get()) != EOF)
	{
		ofs << c;
	}
	ifs.close();
	ofs.close();
}

void Text(int gamer_count)
{
	FormatText();

	write_txt_name = "file01.txt";
	read_txt_name = "file02.txt";
	sorted_line_len = 0;
	while (sorted_line_len < Text_lines)
	{
		text_complited = false;
		sorted_line_len = sorted_line_len ? sorted_line_len * gamer_count : 1;
		now_write_len = 0;
		complited_sort_line = 0;
		now_sorted_line = 0;
		SwapWriteAndRead();
		ClearText(write_txt_name);
		while (!text_complited && sorted_line_len < Text_lines)
		{

			LoserTree tree(gamer_count);
			int len = 0;
			tree.PrintGamers();
			cout << "-------------------------------------" << endl;
			int array_sorted[write_len] = {};
			while (!tree.empty())
			{
				array_sorted[len] = tree.GetWin();
				tree.PopFront();
				if (++len >= write_len)
				{
					WriteText(array_sorted, len);
					len = 0;
				}
			}
			//最后一次填写，因为会有漏的那不满write_len的
			WriteText(array_sorted, len);
			complited_sort_line += gamer_count * sorted_line_len;
			now_sorted_line = complited_sort_line;
		}

		cout << "一次完成" << endl;
	}
	//因为最后还进行了一次交换，所以应该是read_txt_name，而不是write
	CopyText(read_txt_name, "result.txt");


}

void start()
{
	read_txt_name = "file02.txt";
	ClearText(read_txt_name);
	write_txt_name = "file01.txt";
	ClearText(write_txt_name);
	Text(6);
}

//int main()
//{
//	start();
//}
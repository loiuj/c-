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
//��ǰ����,ֻ��Ϊ������ÿ�
int now_write_len;
//�ж������Ƿ����
bool text_complited = false;
//��������
int Text_lines;
//�����ļ�
string read_txt_name;
//д���ļ�
string write_txt_name;

//��ǰ��˳��ĳ���
int sorted_line_len;
//��ǰ����������
int complited_sort_line;
//��ǰ���������
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
		//�������򣬽�ÿһ��С�鴦���һ�������
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

//����ģ��Ӵ����зֿ��ȡ���ݣ�Ȼ����봫��Ķ����У�����ļ���û�����ݻ��ߴ�ʧ���˷���false
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
	Gamer(bool)//��Ϊһ������Ĵ���
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

	//���ض�ͷԪ��
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
	//�ǵ�һ������ȡ���Ҫ�����Լ�����һ������������
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
			gamers_[0] = NULL;//�����λ�ÿճ���
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
		if (gamers_[gamer_index] != NULL)//ȷ�������߲���NULL
		{
			//���嵱ǰ������
			Gamer* self = gamers_[gamer_index];
			//��һ�αȽϵ�ʱ��͸��ڵ�Ƚ�
			int rival = gamer_index / 2;
			//������ڵ��ǿյģ���ô���Լ���ռ�����λ��
			//0�����λ�ò�������ռ�õģ���Ϊ������ȥ
			while (gamers_[rival] != NULL && rival)
			{
				//��Ϊ���ǴӴ�С������������Լ��ȸ��ڵ�����Լ�ռ�����λ��
				//��������������û�����ݣ�������ط�����ռ��
				//�������ط�û�����ݣ�Ĭ����Ϊ���ֵ�������Զ��������λ��
				if (gamers_[rival]->HasData() && (!self->HasData() || self->front() > gamers_[rival]->front()))
				{
					Gamer* tmp = self;
					self = gamers_[rival];
					gamers_[rival] = tmp;
				}
				rival = rival / 2;//����ÿ�κ��Լ��ĸ��ڵ�Ƚ�
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
			//���һ����д����Ϊ����©���ǲ���write_len��
			WriteText(array_sorted, len);
			complited_sort_line += gamer_count * sorted_line_len;
			now_sorted_line = complited_sort_line;
		}

		cout << "һ�����" << endl;
	}
	//��Ϊ��󻹽�����һ�ν���������Ӧ����read_txt_name��������write
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
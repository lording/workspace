/*
	��Ŀ���ӣ�
	https://www.nowcoder.com/questionTerminal/eaf5b886bd6645dd9cfb5406f3753e15?f=discussion
*/


#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#define UP  'U'
#define DOWN 'D'
#define MAXCOUNT 4

class Playlist
{
public:
	explicit Playlist(const int n) : m_count(n)
	{
		m_pos = 0;
		int len = m_count < MAXCOUNT ? m_count : MAXCOUNT;
		for (int i = 0; i < len; ++i)
		{
			m_display.push_back(i + 1);
		}
	}

	//����ָ��ƶ�
	bool Move(const std::string& str)
	{
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (str.at(i) == UP)
			{
				MoveUp();
			}
			else if (str.at(i) == DOWN)
			{
				MoveDown();
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	//�����ƶ�
	void MoveUp()
	{
		if (m_pos > 0)
		{
			m_pos -= 1;
			return;
		}

		assert(m_pos == 0);
		//��Ը�������<=��Ļ�����ʾ����
		if (m_count <= MAXCOUNT)
		{
			m_pos = m_count - 1;
			return;
		}

		//��Ը�������>��Ļ�����ʾ����
		if (m_display[m_pos] == 1)
		{
			m_pos = MAXCOUNT - 1;
			for (int i = 0; i < MAXCOUNT; ++i)
			{
				m_display[i] = m_count - MAXCOUNT + i + 1;
			}
		}
		else
		{
			for (int i = 0; i < MAXCOUNT; ++i)
			{
				m_display[i] -= 1;
			}
		}
	}

	//�����ƶ�
	void MoveDown()
	{
		//��Ը�������<=��Ļ�����ʾ����
		if (m_count <= MAXCOUNT)
		{
			if (m_pos == m_count - 1) //���һ��
			{
				m_pos = 0;
			}
			else
			{
				m_pos += 1;
			}
			return;
		}

		//��Ը�������>��Ļ�����ʾ����
		if (m_pos < MAXCOUNT - 1)
		{
			m_pos += 1;
			return;
		}

		assert(m_pos == MAXCOUNT - 1);
		//���������Ϊ���һ�׸���
		if (m_display[m_pos] == m_count)
		{
			m_pos = 0;
			for (int i = 0; i < MAXCOUNT; ++i)
			{
				m_display[i] = i + 1;
			}
		}
		else//������͵��������һ�׸���
		{
			for (int i = 0; i < MAXCOUNT; ++i)
			{
				m_display[i] += 1;
			}
		}
	}

	void Display()
	{
		int len = m_count < MAXCOUNT ? m_count : MAXCOUNT;
		for (int i = 0; i < len; ++i)
		{
			std::cout << m_display[i] << " ";
		}
		std::cout << std::endl;
		std::cout << m_display[m_pos] << std::endl;
	}
private:
	int m_count;    //����������
	int m_pos;      //[0, 3)
	std::vector<int> m_display; //��ʾ��������MAXCOUNT
};


int main()
{
	int n;
	std::string str;
	while (std::cin >> n >> str)
	{
		Playlist playlist(n);
		playlist.Move(str);
		playlist.Display();
	}
	return 0;
}
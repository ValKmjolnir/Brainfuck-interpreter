#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <cstring>

class brainfuck_interpreter
{
	private:
		std::vector<char> memory;
		std::vector<char> resource;
		std::vector<int>  bracket_pair;
		std::string command;
		std::string enter;
		void init();
		void str_input();
		void file_input();
		void print_resource();
		bool parse();
		int  loop_runtime(int,int,int&);
		void runtime();
	public:
		brainfuck_interpreter()
		{
			memory.clear();
			resource.clear();
			bracket_pair.clear();
			command.clear();
			return;
		}
		~brainfuck_interpreter()
		{
			memory.clear();
			resource.clear();
			bracket_pair.clear();
			command.clear();
			return;
		}
		void repl_interpreter();
		void main_interpreter();
};
void brainfuck_interpreter::init()
{
	resource.clear();
	memory.clear();
	bracket_pair.clear();
	std::vector<char> tmp_mem;
	std::vector<char> tmp_res;
	std::vector<int> tmp_bck;
	memory.swap(tmp_mem);
	resource.swap(tmp_res);
	bracket_pair.swap(tmp_bck);
	return;
}
void brainfuck_interpreter::str_input()
{
	for(int i=0;i<command.length();++i)
		resource.push_back(command[i]);
	return;
}
void brainfuck_interpreter::file_input()
{
	std::ifstream fin(command,std::ios::binary);
	if(fin.fail())
	{
		std::cout<<">> [error] cannot open file: "<<command<<" ."<<std::endl;
		fin.close();
		return;
	}
	while(!fin.eof())
	{
		char tmp=fin.get();
		if(fin.eof())
			break;
		resource.push_back(tmp);
	}
	fin.close();
	return;
}
void brainfuck_interpreter::print_resource()
{
	if(resource.empty())
	{
		std::cout<<">> null."<<std::endl;
		return;
	}
	int line=1;
	int res_len=resource.size();
	std::cout<<line<<" ";
	for(int i=0;i<res_len;++i)
	{
		if(resource[i]=='\n')
		{
			++line;
			std::cout<<std::endl<<line<<" ";
		}
		else if(resource[i]>0)
			std::cout<<resource[i];
		else
			std::cout<<'?';
	}
	std::cout<<std::endl;
	return;
}
bool brainfuck_interpreter::parse()
{
	std::stack<int> bracket_stack;
	bracket_pair.clear();
	int res_len=resource.size();
	for(int i=0;i<res_len;++i)
	{
		if(resource[i]=='[')
			bracket_stack.push(i);
		if(resource[i]==']')
		{
			if(!bracket_stack.empty())
			{
				bracket_pair.push_back(bracket_stack.top());
				bracket_pair[bracket_stack.top()]=i;
				bracket_stack.pop();
			}
			else
			{
				std::cout<<">> [error] lack \'[\' ."<<std::endl;
				return false;
			}
		}
		else
			bracket_pair.push_back(-1);
	}
	if(!bracket_stack.empty())
	{
		std::cout<<">> [error] lack \']\' ."<<std::endl;
		return false;
	}
	return true;
}
int brainfuck_interpreter::loop_runtime(int begin_loop,int loop_condition,int& ptr)
{
	int end_loop=-1;
	while(memory[loop_condition])
	{
		for(int i=begin_loop+1;;++i)
		{
			if(resource[i]=='+')
				++memory[ptr];
			else if(resource[i]=='-')
				--memory[ptr];
			else if(resource[i]=='.')
				std::cout<<memory[ptr];
			else if(resource[i]==',')
				memory[ptr]=std::getchar();
			else if(resource[i]=='>')
			{
				++ptr;
				if(ptr>=memory.size())
					memory.push_back(0);
			}
			else if(resource[i]=='<')
			{
				--ptr;
				if(ptr<0)
				{
					std::cout<<">> [error] SIGSEGV ."<<std::endl;
					return -1;
				}
			}
			else if(resource[i]=='[')
			{
				int ptr_place=ptr;
				i=loop_runtime(i,ptr_place,ptr);
				if(i<0)
					return -1;
			}
			else if(resource[i]==']' && bracket_pair[i]==begin_loop)
			{
				end_loop=i;
				break;
			}
		}
	}
	return end_loop;
}
void brainfuck_interpreter::runtime()
{
	int res_len=resource.size();
	int ptr=0;
	memory.push_back(0);
	for(int i=0;i<res_len;++i)
	{
		if(resource[i]=='+')
			++memory[ptr];
		else if(resource[i]=='-')
			--memory[ptr];
		else if(resource[i]=='.')
			std::cout<<memory[ptr];
		else if(resource[i]==',')
			memory[ptr]=std::getchar();
		else if(resource[i]=='>')
		{
			++ptr;
			if(ptr>=memory.size())
				memory.push_back(0);
		}
		else if(resource[i]=='<')
		{
			--ptr;
			if(ptr<0)
			{
				std::cout<<">> [error] SIGSEGV ."<<std::endl;
				break;
			}
		}
		else if(resource[i]=='[')
		{
			int ptr_place=ptr;
			i=loop_runtime(i,ptr_place,ptr);
			if(i<0)
				break;
		}
	}
	std::cout<<std::endl;
	return;
}
void brainfuck_interpreter::repl_interpreter()
{
	std::cout<<">> [Brainfuck]"<<std::endl;
	while(1)
	{
		init();
		std::cout<<">> ";
		std::cin>>command;
		std::getline(std::cin,enter);
		str_input();
		if(command=="exit")
			break;
		if(parse())
			runtime();
	}
	return;
}
void brainfuck_interpreter::main_interpreter()
{
	init();
	std::cout<<">> [Brainfuck]"<<std::endl;
	while(1)
	{
		std::cout<<">> ";
		std::cin>>command;
		std::getline(std::cin,enter);
		if(command=="exit")
			break;
		else if(command=="print")
			print_resource();
		else if(command=="run")
		{
			if(parse())
				runtime();
		}
		else
		{
			init();
			file_input();
		}
	}
	return;
}

brainfuck_interpreter bf;
int main()
{
	// two ways of using bf interpreter
	bf.repl_interpreter();
	bf.main_interpreter();
	return 0;
}

#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<vector>
#include<map>
#include<list>

using namespace std;

class Suffix
{
public:
	int num;
	string name;
	Suffix():num(0),name(""){}
	Suffix(string s,int t):num(t),name(s){}
};

int main()
{
	ifstream fin("dictionary.txt");
	set<string> dic;
	string word = "";

	cout<<"Generating dictionary..."<<endl;

	while(!fin.eof())
	{
		getline(fin,word);
		dic.insert(word);
	}

	cout<<"Completed."<<endl;

	//for(set<string>::iterator iter=dic.begin();iter!=dic.end();iter++)
	//{
	//	cout<<*iter<<endl;
	//}

	map<string,int> SuffixMap;

	string suffix="";


	unsigned int num=0;

	while(true)
	{
		cout<<"Input the number of letters of suffix : ";
		cin>>num;

		cout<<"Searching..."<<endl;

		set<string>::iterator siter;
		for(siter=dic.begin();siter!=dic.end();siter++)
		{
			int size = siter->size();
			if (size>=num)
			{
				suffix = siter->substr(size-num,num);
				SuffixMap[suffix]++;
			}
		}

		vector<Suffix> SuffixTable;

		map<string,int>::iterator miter;

		for(miter = SuffixMap.begin();miter!=SuffixMap.end();miter++)
		{
			Suffix temp((miter->first),(miter->second));
			if (miter==SuffixMap.begin())
			{
				SuffixTable.push_back(temp);
				continue;
			}
			int i=0;
			vector<Suffix>::iterator viter;

			for (viter = SuffixTable.begin();viter != SuffixTable.end();viter++)
			{
				if (i>10)
					break;
				if (temp.num > viter->num)
				{
					SuffixTable.insert(viter,temp);
					break;
				}
				else if(viter==SuffixTable.end())
				{
					SuffixTable.push_back(temp);
					break;
				}
				i++;
			}
		}

		Suffix printtemp;
		int size=SuffixTable.size();
		for (int j=0;j<size;j++)
		{
			if(j>=10)
				break;
			printtemp = SuffixTable[j];
			cout<<printtemp.name<<'\t'<<printtemp.num<<endl;
		}

		string s;
		int NumOfSuffix=0;
		cout<<"Input a suffix : ";
		cin>>s;
		for(siter=dic.end();siter!=dic.begin();siter--)
		{
			if(siter==dic.end())
			{
				siter--;
				continue;
			}
			int size = siter->size();
			if (size>=num)
			{
				if(siter->substr(size-num,num)==s)
				{
					cout<<*siter<<endl;
					NumOfSuffix++;
				}
			}
		}
		cout<<"Number of "<<s<<" "<<NumOfSuffix<<endl;

	}

	system("pause");
	return 0;
}
#include<bits/stdc++.h>

using namespace std;

vector<int> sort_order;
string order;
vector<int> block_line(100000, 0);
vector<int> curr_line(100000, 0);
int line_size = 0;
string outfile;
priority_queue<pair<vector<string>,int>,vector<pair<vector<string>,int> >,greater<pair<vector<string>,int> > > pq;
priority_queue<pair<vector<string>,int>,vector<pair<vector<string>,int> > > pq1;

vector<string> strSplit(string str, char delim)
{
        string token;
        vector<string> tokens;
        int i;
        for(i=0; i<str.size(); i++)
        {
                if(str[i] != delim)
                {
                        token += str[i];
                }
                else
                {
                        tokens.push_back(token);
                        token.clear();
                }
        }
        tokens.push_back(token);
        return tokens;
}

string getFileName(int num)
{
                stringstream ss;
                ss << num;
                string block_name = "file" + ss.str() + ".txt";
                //ss.close();
                return block_name;
}

void pushLine(int blocknum, int num)
{
        int i;
        if(block_line[blocknum] < num)
        {
                cout << "return" << endl;
                return;
        }
        string line;
        fstream file(getFileName(blocknum).c_str());
        file.seekg((num-1)*(line_size+1));
        getline(file, line);
        file.close();
        vector<string> tmp = strSplit(line, ' ');
        if(order == "asc")
        {
                pq.push(make_pair(tmp, blocknum));
        }
        else if(order == "desc")
        {
                pq1.push(make_pair(tmp, blocknum));
        }
}

void mergeBlocks_asc(int num)
{
        vector<string> tmp;
        string line;
        int i;
        for(i=1;i<=num;i++)
        {
                curr_line[i]++;
                pushLine(i, curr_line[i]);
        }
        cout << "pq created" << endl;
        ofstream output(outfile.c_str());
        while(!pq.empty())
        {
                pair<vector<string>, int>p = pq.top();
                pq.pop();
                tmp = p.first;
                for(i=0; i<tmp.size(); i++)
                {
                        output << tmp[i];
                        if(i != tmp.size()-1)
                                output << " ";
                }output << endl;
                curr_line[p.second]++;
          //      cout << p.second << endl;
                pushLine(p.second, curr_line[p.second]);
        }
        cout << "done" << endl;
}

void mergeBlocks_desc(int num)
{
        vector<string> tmp;
        string line;
        int i;
        for(i=1;i<=num;i++)
        {
                curr_line[i]++;
                pushLine(i, curr_line[i]);
        }
        cout << "pq created" << endl;
        ofstream output("output.txt");
        while(!pq1.empty())
        {
                pair<vector<string>, int>p = pq1.top();
                pq1.pop();
                tmp = p.first;
                for(i=0; i<tmp.size(); i++)
                {
                        output << tmp[i];
                        if(i != tmp.size()-1)
                                output << " ";
                }output << endl;
                curr_line[p.second]++;
          //      cout << p.second << endl;
                pushLine(p.second, curr_line[p.second]);
        }
        cout << "done" << endl;
}


bool compare(vector<string> a, vector<string> b)
{
        for(int i=0; i<sort_order.size(); i++)
        {
                if(order == "asc")
                {
                        if(a[sort_order[i]] < b[sort_order[i]])
                                return true;
                        else if(a[sort_order[i]] > b[sort_order[i]])
                                return false;
                }
                else if(order == "desc")
                {
                        if(a[sort_order[i]] < b[sort_order[i]])
                                return false;
                        else if(a[sort_order[i]] > b[sort_order[i]])
                                return true;
                }
        }
        return false;
}

void sortBlock(string name)
{
        ifstream b(name.c_str());
        string line;
        int i, count = 0;
        vector<vector<string> > bvec;
        while(getline(b, line))
        {
                vector<string> tmp = strSplit(line, ' ');
                bvec.push_back(tmp);
        }      
        b.close();  
/*        for(i=0; i<bvec.size(); i++)
        {
                for(int j=0; j<bvec[i].size(); j++)
                {
                        cout << bvec[i][j] << " ";
                }cout << endl;
        }cout << endl;*/
        sort(bvec.begin(), bvec.end(), compare);
/*        for(i=0; i<bvec.size(); i++)
        {
                for(int j=0; j<bvec[i].size(); j++)
                {
                        cout << bvec[i][j] << " ";
                }cout << endl;
        }*/

        ofstream b1(name.c_str());
        for(i=0; i<bvec.size(); i++)
        {
                for(int j=0; j<bvec[i].size(); j++)
                {
                        b1 << bvec[i][j];
                        if(j != (bvec[i].size()-1))
                        {
                                b1 << " ";
                        }
                }
                b1 << endl;
        }
        b1.close();
}

int main(int argc,char *argv[])
{
        int i,j,k;
        vector<string> args;
        for(i=1; i<argc; i++)
        {
                args.push_back(argv[i]); 
        }
        for(i=0; i<args.size(); i++)
        {
                cout << args[i] << endl;
        }
        outfile = args[1];
        int mem = atoi(args[2].c_str());
        order = args[3];

        map<string, int> colmap;

        ifstream md("metadata.txt");
        string line;
        int coln = 0;
        while(getline(md, line))
        {
                vector<string> tmp = strSplit(line, ',');
                colmap[tmp[0]] = coln++;
        }
        for(i=4; i<args.size(); i++)
        {
                sort_order.push_back(colmap[args[i]]);
        }
        md.close();

        ifstream input(args[0].c_str());
        getline(input, line);
        line_size = line.size();
        int lines = 1;
        while(getline(input, line))
        {
                lines++;
        }
        input.close();
        long long int total_data = lines*line_size;
        int num_blocks = total_data/(mem*1024*1024); 
        if(total_data%(mem*1024*1024) != 0)
                num_blocks++;
        long long int block_lines = lines/num_blocks;
        cout << "Number of blocks: " << num_blocks << "  Number of lines in each block: " << block_lines << endl;

        ifstream input1(args[0].c_str());
        for(int i=1;i<=num_blocks;i++)
        {
                stringstream ss;
                ss << i;
                string block_name = "file" + ss.str() + ".txt";
                ofstream blocks;
                blocks.open(block_name.c_str());
                long long int cnt = 0;
                while(cnt < block_lines)
                { 
                        getline(input1, line);
                        blocks << line << endl;
                        block_line[i]++;
                        cnt++;

                        /*if(!getline(input1, line))
                        {
                                break;
                        }*/
                }
                blocks.close();
        }
        input1.close();
        //Sort the blocks
        for(int i=1;i<=num_blocks;i++)
        {
                stringstream ss;
                ss << i;
                string block_name = "file" + ss.str() + ".txt";
                sortBlock(block_name);
        }
	if(order == "asc")	
        {
		mergeBlocks_asc(num_blocks);
	}
	else if(order == "desc")
	{
		mergeBlocks_desc(num_blocks);
	}
        return 0;
}

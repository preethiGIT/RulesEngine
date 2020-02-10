#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits.h>


using namespace std;

class Person{
public:
  int credit_score;
  string state;
  Person(int cs, string s)
  {
    credit_score = cs;
    state = s;
  }
  void display()
  {
    cout<<"person class created"<<endl;
    cout<<this->credit_score<<endl;
    cout<<this->state<<endl;
  }
};

class Product{
public:
  double interest_rate;
  bool disqualified;
  string name;
  Product(double ir, bool d, string n)
  {
    interest_rate = ir;
    disqualified = d;
    name = n;
  }
  void display()
  {
    cout<<this->interest_rate<<endl;
    cout<<this->disqualified<<endl;
  }
};

class RulesEngine{
public:
  void runRules(Person& p,Product& pr, stringstream& rules)
  {
    string line;
    while ( getline (rules,line) )
    {
      line.erase(remove( line.begin(), line.end(), '\"' ),
                 line.end());
      cout << line << '\n';
      vector <string> tokens;
      // stringstream class check1
      stringstream check1(line);
      string intermediate;
      // Tokenizing w.r.t. to ";""
      while(getline(check1, intermediate, ';'))
      {
        tokens.push_back(intermediate);
      }
      // Printing the token vector
      for(int i = 0; i < tokens.size(); i++)
      {
        cout << tokens[i] << '\n';
        
        
        //Condition to check the state
        if(tokens[i] == "check_state")
        {
          string str = tokens[1];
          if(p.state == str)
          {
            pr.disqualified = true;
          }
        }
        //Condition to check score greater than 720
        if(tokens[i] == "check_score_greater")
        {
          int str = stoi(tokens[1]);
          if(p.credit_score >= str)
          {
            pr.interest_rate-=0.3;
            
          }
        }
        //Condition to check score less than 720
        if(tokens[i] == "check_score_lesser")
        {
          int str = stoi(tokens[1]);
          if(p.credit_score < str)
          {
            pr.interest_rate+=0.5;
            
          }
        }
        //Condition to check product name 7-1 ARM
        if(tokens[i] == "check_product_name")
        {
          string str1 = (tokens[1]);
          cout<<pr.name<<":"<<str1<<endl;
          if(pr.name == str1)
          {
            pr.interest_rate+=0.5;
            
          }
        }
      }
    }
  }
};

stringstream loadRules(){
  ifstream myfile ("file.txt");
  stringstream sstream;
  if (myfile.is_open()){
    sstream << myfile.rdbuf();
  }
  myfile.close();
  return sstream;
}

int main()
{
  int score;
  string state, name, line;
  std::cin.clear();
  cout<<"enter the credit_score and state of person"<<endl;
  cin>>score>>state;
  std::cin.clear();
  cout<<"enter name of product "<<endl;
  cin.ignore();
  getline(cin,name);
  
  Person *person=new Person(score,state);
  Product *product = new Product(5.0,false,name);
  stringstream rules= loadRules();
  RulesEngine *rules_engine = new RulesEngine();
  rules_engine->runRules(*person,*product,rules);
  product->display();
  return 0;
}


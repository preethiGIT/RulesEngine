#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits.h>
#include <stdlib.h>


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
    cout<<"product.interest_rate:"<<this->interest_rate<<endl;
    cout<<"product.disqualified:"<<((this->disqualified)?"true":"false")<<endl;
  }
};

class RulesEngine{
public:
  void runRules(Person& p,Product& pr, vector<string> rules)
  {
    string line;
    for (int i=0; i<rules.size();i++)
    {
      line=rules[i];
      line.erase(remove(line.begin(),line.end(),'\"' ),line.end());
      vector<string> tokens;
      stringstream check1(line);
      string intermediate;
 
      // Tokenizing w.r.t. to ";""
      while(getline(check1, intermediate, ';'))
      {
        tokens.push_back(intermediate);
      }
      //Condition to check the state
      if(tokens[0] == "check_state")
      {
        string state = tokens[1];
        if(p.state == state)
        {
          pr.disqualified = true;
        }
      }
      //Condition to check score greater than 720
      if(tokens[0] == "check_score_greater")
      {
        int score = stoi(tokens[1]);
        double rate;
        stringstream ss(tokens[2]);
        ss >> rate;
        if(p.credit_score >= score)
        {
          pr.interest_rate-=rate;
        }
      }
      //Condition to check score less than 720
      if(tokens[0] == "check_score_lesser")
      {
        int score = stoi(tokens[1]);
        double rate;
        stringstream ss(tokens[2]);
        ss >> rate;
        if(p.credit_score < score)     
        {
          pr.interest_rate+=rate;
        }
      }
      //Condition to check product name 7-1 ARM
      if(tokens[0] == "check_product_name")
      {
        string name = (tokens[1]);
        double rate;
        stringstream ss(tokens[2]);
        ss >> rate;
        if(pr.name == name)
        {
          pr.interest_rate+=rate;
        }
      }
    }
  }
};

vector<string> loadRules(){
  ifstream myfile ("rules.txt");
  vector<string> rulesString; 
  string line;
  if (myfile.is_open()){
    while(getline(myfile,line)){
      rulesString.push_back(line);
    }
  }
  myfile.close();
  return rulesString;
}

int main()
{
  int score;
  string state, name, line;
  cout<<"enter the credit_score and state of person"<<endl;
  cin>>score>>state;
  cout<<"enter name of product "<<endl;
  cin.ignore();
  getline(cin,name);
  
  Person *person=new Person(score,state);
  Product *product = new Product(5.0,false,name);
  vector<string> rules = loadRules();
  RulesEngine *rules_engine = new RulesEngine();
  rules_engine->runRules(*person,*product,rules);
  product->display();
  return 0;
}


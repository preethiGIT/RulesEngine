Project Title:
Rules Engine

Description:
This will explain how to run RulesEngine.cpp file.The rules are stored in a text file as comma seperated values. Each rule has 3 parameters (action,condition,parameter).LoadRules() function will parse through the file and store the values in a datastructure as vector of strings.runRules() function will parse through each line and apply the rules on the person object. 

Commands to execute on terminal:
g++ RulesEngine.cpp -o RulesEngine.out
./RulesEngine.out 
Enter the requested parameters per requirement.
The output will display the product information based on the applies rules.

Ex:
enter the credit_score and state of person
720
Florida        
enter name of product 
7-1 ARM
product.interest_rate:5.2
product.disqualified:false




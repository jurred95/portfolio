#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include "bst.h"
////jared j smith 1005002635

//  add any other needed include files..

int b_search(std::string * arr, std::string dic_word){

    int left = 0;
    int i = 0;
    int right = 1095840 - 1;
    int found = 0;
    while (right >= left && found == 0){
      int m = (left + right);
        if (arr[m] == dic_word){
            found = 1;
          }else if (dic_word < arr[m]){
            right = m - 1;
          }
        else{
            left = m + 1;
          }
          i++;
      }
    if (found == 0)
        return 0;
    else{
        return 1;
      }
}


std::string* arr_and_read(char * file){
  std::string line;
  std::string dic_word;
  std::string *arr = new std::string[1095840];

  int i =0;
  std::ifstream infile(file);
if (!infile.fail()){
  while(std::getline(infile, line))
  {
    std::istringstream iss(line);

    while(iss >> dic_word)
    {
       dic_word.erase(std::remove_if (dic_word.begin(), dic_word.end(), ispunct), dic_word.end());
       std::transform(dic_word.begin(), dic_word.end(), dic_word.begin(), ::tolower);
          arr[i] = dic_word;
          i++;
        }
    }
    return arr;
  }else{
    std::cerr <<  ": no such file directory" << std::endl;
  }
 }

void tree_and_read(char * file, std::string * dictionary_b, std:: string * dictionary, std::string fileName){
        std::string line;
        std::string story_word;
        BSTree  not_tree_one;
        BSTree  not_tree_two;
        BSTree my_story;
        std::ofstream ofile;
        std::string Text(file);
        int i =0;
        std::ifstream infile(file);

if (!infile.fail()){
        while(std::getline(infile, line))
        {

          std::istringstream iss(line);

        while(iss >> story_word)
        {
            story_word.erase(std::remove_if (story_word.begin(), story_word.end(), ispunct), story_word.end());
            std::transform(story_word.begin(), story_word.end(), story_word.begin(), ::tolower);

            if(b_search(dictionary_b, story_word) == 0){
              not_tree_one.insert(story_word);
            }
            if(b_search(dictionary, story_word) == 0){
              not_tree_two.insert(story_word);
            }

            my_story.insert(story_word);
            i++;
          }
        }
      }else{
				std::cerr <<  ": no such file directory" << std::endl;
			}


    const char * out_file = (fileName).c_str();

        ofile.open (out_file);
        ofile << Text;
        std::cout << std::endl;
         if(Text == "AliceInWonderland.txt"){
           std:: cout << std::endl;

           std::streambuf *oldbuf = std::cout.rdbuf(); //save

           std::cout.rdbuf(ofile.rdbuf());

           std::cout<< std::endl<<" this is number of words not appearing in the first dictionary and the words" <<std::endl;

           not_tree_one.print_list(not_tree_one.get_size());

           std::cout << "amount: ";
           ofile << not_tree_one.get_size();

           std::cout<< std::endl<<"****************************" <<std::endl;

           std::cout<< std::endl<<" this is number of words not appearing in the second dictionary and the words" <<std::endl;

           not_tree_two.print_list(not_tree_two.get_size());

           std::cout << "amount: ";
           ofile << not_tree_two.get_size();

           std::cout<< std::endl<<"****************************" <<std::endl;

           std::cout<< std::endl<<" This is the total number of words" <<std::endl;

           std::cout << "amount: ";
           ofile << i;

           std::cout<< std::endl<<" This is the total number of unique words" <<std::endl;

           std::cout << "amount: ";
           ofile << my_story.get_size();
           std::cout<< std::endl<<"****************************" <<std::endl;


           std::cout<<std::endl<< " this is the word range" <<std::endl;

           my_story.print_range("crowd","cupboards");
           std::cout << "amount: ";
           ofile << my_story.get_count();

           //my_story.get_count();

           std::cout.rdbuf(oldbuf);
        }
         if(Text == "WarAndPeace.txt"){
           std:: cout << std::endl;

           std::streambuf *oldbuf = std::cout.rdbuf(); //save

           std::cout.rdbuf(ofile.rdbuf());

           std::cout<< std::endl<<" this is number of words not appearing in the first dictionary and the words" <<std::endl;

           not_tree_one.print_tree(not_tree_one.get_size());

           std::cout << "amount: ";
           ofile << not_tree_one.get_size();

           std::cout<< std::endl<<"****************************" <<std::endl;

           std::cout<< std::endl<<" this is number of words not appearing in the second dictionary and the words" <<std::endl;

           not_tree_two.print_tree(not_tree_two.get_size());

           std::cout << "amount: ";
           ofile << not_tree_two.get_size();

           std::cout<< std::endl<<"****************************" <<std::endl;

           std::cout<< std::endl<<" This is the total number of words" <<std::endl;

           std::cout << "amount: ";
           ofile << i;

           std::cout<< std::endl<<" This is the total number of unique words" <<std::endl;

           std::cout << "amount: ";
           ofile << my_story.get_size();
           std::cout<< std::endl<<"****************************" <<std::endl;


           std::cout<<std::endl<< " this is the word range" <<std::endl;

           my_story.print_range("all","alliance");
           std::cout << "amount: ";
           ofile << my_story.get_count();

           //my_story.get_count();

           std::cout.rdbuf(oldbuf);
        }
       if(Text == "ATaleOfTwoCities.txt"){
          std:: cout << std::endl;

          std::streambuf *oldbuf = std::cout.rdbuf(); //save

          std::cout.rdbuf(ofile.rdbuf());

          std::cout<< std::endl<<" this is number of words not appearing in the first dictionary and the words" <<std::endl;

          not_tree_one.print_tree(not_tree_one.get_size());

          std::cout << "amount: ";
          ofile << not_tree_one.get_size();

          std::cout<< std::endl<<"****************************" <<std::endl;

          std::cout<< std::endl<<" this is number of words not appearing in the second dictionary and the words" <<std::endl;

          not_tree_two.print_tree(not_tree_two.get_size());

          std::cout << "amount: ";
          ofile << not_tree_two.get_size();

          std::cout<< std::endl<<"****************************" <<std::endl;

          std::cout<< std::endl<<" This is the total number of words" <<std::endl;

          std::cout << "amount: ";
          ofile << i;

          std::cout<< std::endl<<" This is the total number of unique words" <<std::endl;

          std::cout << "amount: ";
          ofile << my_story.get_size();
          std::cout<< std::endl<<"****************************" <<std::endl;


          std::cout<<std::endl<< " this is the word range" <<std::endl;

          my_story.print_range("code","coinage");
          std::cout << "amount: ";
          ofile << my_story.get_count();

          //my_story.get_count();

          std::cout.rdbuf(oldbuf);
        }
       if(Text == "PrideAndPrejudice.txt"){
         std:: cout << std::endl;

         std::streambuf *oldbuf = std::cout.rdbuf(); //save

         std::cout.rdbuf(ofile.rdbuf());

         std::cout<< std::endl<<" this is number of words not appearing in the first dictionary and the words" <<std::endl;

         not_tree_one.print_tree(not_tree_one.get_size());

         std::cout << "amount: ";
         ofile << not_tree_one.get_size();

         std::cout<< std::endl<<"****************************" <<std::endl;

         std::cout<< std::endl<<" this is number of words not appearing in the second dictionary and the words" <<std::endl;

         not_tree_two.print_tree(not_tree_two.get_size());

         std::cout << "amount: ";
         ofile << not_tree_two.get_size();

         std::cout<< std::endl<<"****************************" <<std::endl;

         std::cout<< std::endl<<" This is the total number of words" <<std::endl;

         std::cout << "amount: ";
         ofile << i;

         std::cout<< std::endl<<" This is the total number of unique words" <<std::endl;

         std::cout << "amount: ";
         ofile << my_story.get_size();
         std::cout<< std::endl<<"****************************" <<std::endl;


         std::cout<<std::endl<< " this is the word range" <<std::endl;

         my_story.print_range("determined","dictated");
         std::cout << "amount: ";
         ofile << my_story.get_count();

         //my_story.get_count();

         std::cout.rdbuf(oldbuf);

        }


      /*  ofile << "Writing this to a file.\n";
        ofile << "Writing this to a file.\n";
        */
        ofile.close();

    }



int main(int argc, char *argv[]) {

  std::string* brit_text_file;
  std::string line;
  std::string* dic_text_file;
  std::string dic_word;
  std::string *arr_one = new std::string[1095840];
  std::string *arr_two = new std::string[1095840];
  BSTree myT1;
  BSTree myT2;
  BSTree myT3;
  BSTree myT4;



      brit_text_file = arr_and_read(argv[1]);

      dic_text_file =  arr_and_read(argv[2]);

    //  4 different trees = tree and read of each story which is the argv's'
    //  BSTree story_file1 = blah blah

    tree_and_read(argv[3], brit_text_file, dic_text_file, "1.txt");
    tree_and_read(argv[4], brit_text_file, dic_text_file, "2.txt");
    tree_and_read(argv[5], brit_text_file, dic_text_file, "3.txt");
    tree_and_read(argv[6], brit_text_file, dic_text_file, "4.txt");

    delete  [] arr_one;
    delete  [] arr_two;
    return 0;
}


      /*BSTree treat;

     //std::cout<<"before line 1"<<std::endl;
      treat.insert("yo");
      treat.insert("yo");
      //std::cout<<"before line 3"<<std::endl;
      treat.insert("pen");
      //std::cout<<"before line 5"<<std::endl;
      treat.insert("is");
      //std::cout<<"before line 7"<<std::endl;
      treat.insert("small");
      //std::cout<<"before line 9"<<std::endl;
      treat.print_list(4);
      //std::cout<<"before line 11"<<std::endl;
      std::cout << "*********************" <<std::endl;
      treat.print_range("pen","yo");

      //std::cout<<"after line 11"<<std::endl;
      */

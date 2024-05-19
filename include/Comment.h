#pragma once 
#include<iostream>
#include<unordered_map>
#include<string>
#ifdef __APPLE__
    #include<ncurses.h>
#endif


class Comment
{
private:
    std::unordered_map< std::string, std::string>* CommentList;
    
public:
    Comment(); // an empty comment space
    Comment(const Comment& other); // declared comment space
    ~Comment();
    Comment& operator = (const Comment& other);

    std::unordered_map<std::string, std::string>& getCommentList() const;
    void setCommentList(const std::unordered_map<std::string, std::string>&); 

    void writeNewComment();   //remember to dynamic allocate in main function
    void showAllComments();  
    void editComment(std::unordered_map<std::string, std::string>& );
    void deleteComment();
    
};
#include "Comment.h"


Comment::Comment() {
    this->CommentList = new std::unordered_map<std::string, std::string>();
};

Comment::Comment(const Comment& other) {
    this->CommentList = new std::unordered_map<std::string, std::string> (other.getCommentList());
}; // the inputList is reading from file

std::unordered_map<std::string, std::string>& Comment::getCommentList() const {
    return *CommentList;
};

//Copy assigment operator:

Comment& Comment::operator=(const Comment& other) {
    if (this !=&other) {
        delete this->CommentList; // free existing memory
        this->CommentList = new std::unordered_map<std::string, std::string>(*other.CommentList);
    }
    return *this;
}

void Comment::setCommentList(const std::unordered_map<std::string, std::string>& InCommentList) {
    *this->CommentList = InCommentList;
    return;
};

void Comment::writeNewComment(){

    #ifdef __APPLE__
        std::string key = "";
        std::string value = "";

        if (initscr() == nullptr) { // Initialize ncurses mode if the screen not been inited
            initscr();
        }
        echo();
        // Display prompts and get input using ncurses
        printw("Please enter your name and the comment you want in this radio!!\n");
        printw("Your name: ");
        refresh(); // Refresh the screen to display the prompt
        char nameBuffer[256]; // Allocate a character array for the name
        getstr(nameBuffer); // Read the name input
        key = nameBuffer; // Convert the character array to a std::string

        printw("\nYour comment: ");
        refresh(); // Refresh the screen to display the prompt
        char commentBuffer[256]; // Allocate a character array for the comment
        getstr(commentBuffer); // Read the comment input
        value = commentBuffer; // Convert the character array to a std::string

        std::unordered_map<std::string, std::string>& comments = getCommentList();
        comments.insert({key, value});
        
        noecho();
        // Display a confirmation message
        printw("You have inserted this comment!!\n");
        refresh(); // Refresh the screen to display the message

    #else
        std::string key = "" ;
        std::string value = "" ;
        std::cout << "Please enter your name and the comment you want in this radio!!" << std::endl;
        std::cout << "Your name: ";
        std::getline(std::cin, key);
        std::cout << "Your comment: ";
        std::getline(std::cin, value);
        (getCommentList())[key] = value;
        std::cout << "You have inserted this comment!!" << std::endl;
        return;

    #endif
    
};   //remember to dynamic allocate in main function

void Comment::showAllComments(){

        #ifdef _WIN32
        if (getCommentList().empty()) {
            std::cout << "No comments available." << std::endl;
        } 
        else {
            std::cout << "Here are all the comments of the radio: " << std::endl; 
            
            for (const auto& comment : getCommentList()) {
                std::cout << comment.first << ": " << comment.second << std::endl;
            }
        }
        #else
            if (initscr() == nullptr) { // Initialize ncurses mode if the screen not been inited
                initscr();
            } 
            auto& commentList = getCommentList(); // Access the comment list
            if (getCommentList().empty()) {
            printw("No comments available.\n");
        } else {
            printw("Here are all the comments of the radio:\n");
            refresh();
            
            for (const auto& comment : getCommentList()) {
                printw("%s: %s\n", comment.first.c_str(), comment.second.c_str());
            }
        }
        #endif
        return;
}; 

void Comment::editComment(std::unordered_map<std::string, std::string>& commentList){
    
    #ifdef _WIN32
    std::string keyToFind = "";
    std::cout << "Enter key to find!";
    std::getline(std::cin, keyToFind);

    //find the key in the map
    auto it = commentList.find (keyToFind);
    if (it != commentList.end()){
        std::cout << "The comment of"  << it -> first << "have found. The comment is: " << it -> second << std::endl;

        //Add new comment
        std::string newValue = "";
        std::cout << "Enter the new comment: ";
        std::cin.ignore(); 
        std::getline(std::cin, newValue);
        commentList[it->first] = newValue;

        std::cout << "The value updated sucessfully!";
    }
    else{
        // If the key is not found, display an error message
        std::cout << "Can not find your comment." << std::endl;
    }
    #else
        std::string keyToFind = "";
        if (initscr() == nullptr) { // Initialize ncurses mode if the screen not been inited
            initscr();
        } 
        printw("Enter key to find: ");
        refresh();

        char keyBuffer[256];
        getstr(keyBuffer);
        keyToFind = keyBuffer;

        auto it = commentList.find(keyToFind);
        if (it != commentList.end()) {
            printw("The comment of %s has been found. The comment is: %s\n", it->first.c_str(), it->second.c_str());
            refresh();

            // Add new comment
            std::string newValue = "";
            printw("Enter the new comment: ");
            refresh();

            char valueBuffer[256];
            getstr(valueBuffer);
            newValue = valueBuffer;
            it->second = newValue;

            printw("The value has been updated successfully!\n");
            refresh();
        } else {
            printw("Cannot find your comment.\n");
            refresh();
        }
    #endif

};

void Comment::deleteComment(){
    #ifdef _WIN32
    std::string keyToFind = "";
    std::cout << "Enter the key of the comment to delete: ";

    std::getline(std::cin, keyToFind);
    auto it = getCommentList().find(keyToFind);
    if (it != getCommentList().end()) {
        getCommentList().erase(it);
        std::cout << "Comment deleted successfully.\n";
    } 
    else {
    std::cout << "Comment not found.\n";
    }
    #else
        if (initscr() == nullptr) { // Initialize ncurses mode if the screen not been inited
            initscr();
        } 
        std::string keyToFind = "";
        printw("Enter the key of the comment to delete: ");
        refresh();

        char keyBuffer[256];
        getstr(keyBuffer);
        keyToFind = keyBuffer;

        auto it = getCommentList().find(keyToFind);
        if (it != getCommentList().end()) {
            getCommentList().erase(it);
            printw("Comment deleted successfully.\n");
        } 
        else {
            printw("Comment not found.\n");
        }
        refresh();
    #endif

};

// Destructor
Comment::~Comment() {
    if (this->CommentList !=nullptr)
        {
            delete this->CommentList; // Free the dynamically allocated memory
        }
};

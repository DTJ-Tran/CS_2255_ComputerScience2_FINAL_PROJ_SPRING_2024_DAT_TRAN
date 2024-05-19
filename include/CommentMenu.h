#pragma once
#include "Menu.h"
#include "Comment.h"
#ifdef __APPLE__
    #include<ncurses.h>
#endif

class CommentMenu : public Menu {

    private:
       
        static const int WRITE_NEW_COMMENT = 0;
        static const int SHOW_ALL_COMMENT = 1;
        static const int EDIT_COMMENT = 2;
        static const int DELETE_COMMENT = 3;
        Comment* CommendHandling;
        
    public:
        static int getWriteNewCom();
        static int getShowAll();
        static int getEdit();
        static int getDelete();

        Comment* getCommentHandling() const;
        void setCommentHandling();
        void handleChoice(int) override;
        CommentMenu();
        CommentMenu(std::string);
        ~CommentMenu();
};




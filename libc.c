#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char book_title[25];
    char author[25];
    int book_isbn;
    bool status;
} Book;

typedef struct {
    char name[25];
    int user_id;
    Book book_list[5];
    int numofbooks;
} User;

void add_newbook(Book booklist[], int *i);
void putbook(Book booklist[], int totalbooks);
void findbook(Book booklist[], char name[], int i);
void deletebook(Book booklist[], int *i);
void add_newuser(User userlist[], int *j);
void putuser(User userlist[], int j);
void finduser(User userlist[], int id, int j);
void borrowbook(User userlist[], Book booklist[], int user_id, int book_isbn, int j, int i);
void returnbook(User userlist[], Book booklist[], int user_id, int book_isbn, int j, int i);
void listborrowedbooks(User userlist[], int user_id, int j);
bool is_isbn_unique(Book booklist[], int totalbooks, int isbn);
bool is_userid_unique(User userlist[], int totalusers, int user_id);

int main() {
    Book booklist[50];
    int totalbooks = 0;
    User userlist[50];
    int totalusers = 0;
    int choice, id, isbn;
    char name[25];
    printf("\n###################################################################################\n");
		printf("\n                           Welcome to The Library  Libro                            \n");
		printf("\n***********************************************************************************\n");
    while (true) {
        printf("\nThe features are:\n");
        printf("1. Add new book\n");
        printf("2. Display all books\n");
        printf("3. Search for a book by title\n");
        printf("4. Delete a book by ISBN\n");
        printf("5. Add new user\n");
        printf("6. Display all users\n");
        printf("7. Search for a user by ID\n");
        printf("8. Borrow a book\n");
        printf("9. Return a book\n");
        printf("10. List borrowed books\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear newline character from the buffer

        switch (choice) {
            case 1:
                add_newbook(booklist, &totalbooks);
                break;
            case 2:
                putbook(booklist, totalbooks);
                break;
            case 3:
                printf("Enter the title of the book to be searched: ");
                fgets(name, 25, stdin);
                name[strcspn(name, "\n")] = 0;  // Remove newline character
                findbook(booklist, name, totalbooks);
                break;
            case 4:
                deletebook(booklist, &totalbooks);
                break;
            case 5:
                add_newuser(userlist, &totalusers);
                break;
            case 6:
                putuser(userlist, totalusers);
                break;
            case 7:
                printf("Enter the user ID to be searched: ");
                scanf("%d", &id);
                getchar();  // Clear newline character from the buffer
                finduser(userlist, id, totalusers);
                break;
            case 8:
                printf("Enter the user ID: ");
                scanf("%d", &id);
                getchar();  // Clear newline character from the buffer
                printf("Enter the ISBN of the book: ");
                scanf("%d", &isbn);
                getchar();  // Clear newline character from the buffer
                borrowbook(userlist, booklist, id, isbn, totalusers, totalbooks);
                break;
            case 9:
                printf("Enter the user ID to return a book: ");
                scanf("%d", &id);
                getchar();  // Clear newline character from the buffer
                printf("Enter the ISBN of the book to be returned: ");
                scanf("%d", &isbn);
                getchar();  // Clear newline character from the buffer
                returnbook(userlist, booklist, id, isbn, totalusers, totalbooks);
                break;
            case 10:
                printf("Enter the user ID to list borrowed books: ");
                scanf("%d", &id);
                getchar();  // Clear newline character from the buffer
                listborrowedbooks(userlist, id, totalusers);
                break;
            case 11:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void add_newbook(Book booklist[], int *i) {
    if (*i >= 50) {
        printf("Book list is full. Cannot add more books.\n");
        return;
    }

    char bookname[25], author[25];
    int isbn;

    printf("Enter the book name: ");
    fgets(bookname, 25, stdin);
    bookname[strcspn(bookname, "\n")] = 0;  // Remove newline character

    printf("Enter the author name: ");
    fgets(author, 25, stdin);
    author[strcspn(author, "\n")] = 0;  // Remove newline character

    printf("Enter valid book ISBN: ");
    scanf("%d", &isbn);
    getchar();  // Clear newline character from the buffer

    if (!is_isbn_unique(booklist, *i, isbn)) {
        printf("ISBN already exists. Please enter a unique ISBN.\n");
        return;
    }

    Book b1;
    strcpy(b1.book_title, bookname);
    strcpy(b1.author, author);
    b1.book_isbn = isbn;
    b1.status = true;
    booklist[*i] = b1;
    (*i)++;
    printf("The new book was added\n");
}

void putbook(Book booklist[], int i) {
    if (i <= 0) {
        printf("There are no books to display\n");
        return;
    }
    printf("The books in the booklist are:\n");
    for (int j = 0; j < i; j++) {
        printf("Book name: %s, Author name: %s, Book ISBN: %d, Book availability: %s\n",
               booklist[j].book_title, booklist[j].author, booklist[j].book_isbn, booklist[j].status ? "yes" : "no");
    }
}

void deletebook(Book booklist[], int *i) {
    int isbn;
    printf("Enter the ISBN of the book to be deleted: ");
    scanf("%d", &isbn);
    getchar();  // Clear newline character from the buffer
    for (int j = 0; j < *i; j++) {
        if (booklist[j].book_isbn == isbn) {
            printf("The deleted book is %s\n", booklist[j].book_title);
            for (int k = j; k < *i - 1; k++) {
                booklist[k] = booklist[k + 1];
            }
            (*i)--;
            return;
        }
    }
    printf("The book doesn't exist. Enter a valid book.\n");
}

void findbook(Book booklist[], char name[], int i) {
    if (i <= 0) {
        printf("There are no books to search\n");
        return;
    }
    for (int j = 0; j < i; j++) {
        if (strcmp(booklist[j].book_title, name) == 0) {
            printf("The book is found\n");
            printf("Book name: %s, Author name: %s, Book ISBN: %d\n",
                   booklist[j].book_title, booklist[j].author, booklist[j].book_isbn);
            return;
        }
    }
    printf("The book doesn't exist. Enter a valid book.\n");
}

void add_newuser(User userlist[], int *j) {
    if (*j >= 50) {
        printf("User list is full. Cannot add more users.\n");
        return;
    }

    char username[25];
    int userid;

    printf("Enter the user name: ");
    fgets(username, 25, stdin);
    username[strcspn(username, "\n")] = 0;  // Remove newline character

    printf("Enter the user ID: ");
    scanf("%d", &userid);
    getchar();  // Clear newline character from the buffer

    if (!is_userid_unique(userlist, *j, userid)) {
        printf("User ID already exists. Please enter a unique user ID.\n");
        return;
    }

    User u1;
    strcpy(u1.name, username);
    u1.user_id = userid;
    u1.numofbooks = 0;
    userlist[*j] = u1;
    (*j)++;
    printf("The new user was added\n");
}

void putuser(User userlist[], int j) {
    if (j <= 0) {
        printf("There are no users to display\n");
        return;
    }
    printf("The users in the userlist are:\n");
    for (int k = 0; k < j; k++) {
        printf("User name: %s, User ID: %d\n", userlist[k].name, userlist[k].user_id);
    }
}

void finduser(User userlist[], int id, int j) {
    if (j <= 0) {
        printf("There are no users to search\n");
        return;
    }
    for (int k = 0; k < j; k++) {
        if (userlist[k].user_id == id) {
            printf("The user is found\n");
            printf("User name: %s, User ID: %d\n", userlist[k].name, userlist[k].user_id);
            return;
        }
    }
    printf("The user doesn't exist. Enter a valid user ID.\n");
}

void borrowbook(User userlist[], Book booklist[], int user_id, int book_isbn, int j, int i) {
    for (int k = 0; k < j; k++) {
        if (userlist[k].user_id == user_id) {
            for (int l = 0; l < i; l++) {
                if (booklist[l].book_isbn == book_isbn && booklist[l].status == true) {
                    if (userlist[k].numofbooks < 5) {
                        booklist[l].status = false;
                        userlist[k].book_list[userlist[k].numofbooks] = booklist[l];
                        userlist[k].numofbooks++;
                        printf("Book borrowed successfully\n");
                        return;
                    } else {
                        printf("User has already borrowed 5 books\n");
                        return;
                    }
                }
            }
            printf("Book is not available or does not exist\n");
            return;
        }
    }
    printf("User ID does not exist\n");
}

void returnbook(User userlist[], Book booklist[], int user_id, int book_isbn, int j, int i) {
    for (int k = 0; k < j; k++) {
        if (userlist[k].user_id == user_id) {
            for (int m = 0; m < userlist[k].numofbooks; m++) {
                if (userlist[k].book_list[m].book_isbn == book_isbn) {
                    for (int l = 0; l < i; l++) {
                        if (booklist[l].book_isbn == book_isbn) {
                            booklist[l].status = true;
                            for (int n = m; n < userlist[k].numofbooks - 1; n++) {
                                userlist[k].book_list[n] = userlist[k].book_list[n + 1];
                            }
                            userlist[k].numofbooks--;
                            printf("Book returned successfully\n");
                            return;
                        }
                    }
                }
            }
            printf("Book not found in user's borrowed list\n");
            return;
        }
    }
    printf("User ID does not exist\n");
}

void listborrowedbooks(User userlist[], int user_id, int j) {
    for (int k = 0; k < j; k++) {
        if (userlist[k].user_id == user_id) {
            if (userlist[k].numofbooks == 0) {
                printf("No books borrowed by this user\n");
                return;
            }
            printf("Books borrowed by user ID %d:\n", user_id);
            for (int m = 0; m < userlist[k].numofbooks; m++) {
                printf("Book name: %s, Author name: %s, Book ISBN: %d\n",
                       userlist[k].book_list[m].book_title, userlist[k].book_list[m].author,
                        userlist[k].book_list[m].book_isbn);
            }
            return;
        }
    }
    printf("User ID does not exist\n");
}

bool is_isbn_unique(Book booklist[], int totalbooks, int isbn) {
    for (int i = 0; i < totalbooks; i++) {
        if (booklist[i].book_isbn == isbn) {
            return false;
        }
    }
    return true;
}

bool is_userid_unique(User userlist[], int totalusers, int user_id) {
    for (int i = 0; i < totalusers; i++) {
        if (userlist[i].user_id == user_id) {
            return false;
        }
    }
    return true;
}

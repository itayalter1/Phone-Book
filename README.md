
---

# 📒 Phone Book Manager  

A command-line phone book management system implemented in C. The program uses a linked list data structure to store and manage contacts, organizing them alphabetically by last name. 🧾

## ✨ Features  
- ➕ Add new contacts  
- ❌ Delete existing contacts  
- 🔍 Search contacts by phone number  
- 📝 Search contacts by name  
- ✏️ Update contact phone numbers  
- 📋 Print all contacts alphabetically  

## 🛠️ Prerequisites  
- 🖥️ GCC compiler  
- 🛠️ Git (for cloning)  

## ⚙️ Installation  
```bash  
git clone https://github.com/yourusername/phone-book.git
```
```bash 
cd phone-book
```
```bash  
gcc -o phonebook phonebook.c  
```  

## ▶️ Usage  
Run the compiled program:  
```bash  
./phonebook  
```  

## 💻 Example Run  
```
Welcome to the phone book manager!  
Choose an option:  
1. Add a new contact to the phone book.  
2. Delete a contact from the phone book.  
3. Find a contact in the phone book by phone number.  
4. Find a contact in the phone book by name.  
5. Update phone number for a contact.  
6. Print phone book.  
7. Exit.  

> 1  
Enter a contact details (<first name> <last name> <phone number>): John Doe 0501234567  
The contact has been added successfully!  

> 6  
John      Doe       0501234567  

> 7  
Bye!  
```

---


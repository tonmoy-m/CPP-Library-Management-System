# 📚 C++ Terminal Library Management System

This repository holds a special milestone: the first official project of my academic journey. Built as a lightweight console application, it was designed to solve a real-world scenario while cementing foundational computer science concepts like Object-Oriented Programming (OOP) and File I/O.

## 🎓 Academic Background

This system was developed collaboratively as a group assignment. 
* **Course:** CSE 1204 - Object-Oriented Programming Language I Sessional
* **Level:** Level 1, Term II
* **Type:** Group Project

## ✨ Features

* **Role-Based Access:** Abstract base `User` class extended by `Admin` and `Student` classes.
* **Admin Panel:** Secure login to dynamically add and remove books from the library catalogue.
* **Student Borrowing:** Users can browse books and borrow them, generating a unique, personalized voucher.
* **Persistent Tracking:** Uses C++ File I/O (`fstream`) to save, verify, and update active book vouchers in real-time.

## 🛠️ Tech Stack

* **Language:** C++
* **Concepts Demonstrated:** Abstract Classes, Virtual Functions, File Stream Processing, Array Manipulation.

## 🚀 How to Run

1. Clone this repository to your local machine.
2. Navigate to the source directory: `cd src`
3. Compile the code: `g++ main.cpp -o library_app`
4. Run the executable: `./library_app` (or `library_app.exe` on Windows)

> **Default Admin Credentials:**
> Username: `admin` | Password: `password`

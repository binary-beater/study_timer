# Study-Rest Timer (C)

A minimal, efficient, and cross-platform C program for managing timed study and rest intervals. Ideal for productivity-focused workflows with local logging and notifications.

---

## Structure

study_timer/
├── main.c
├── README.md
├── .gitignore
├── study_timer.exe
└── log
    └── study_log.txt

--- 

##  Features

-  Customizable **study** and **rest** durations
-  Configurable **total session time**
-  **Beep notifications** after each interval
-  **Timestamped logging** to `log/study_log.txt`
-  Cross-platform support (**Windows** and **Linux/macOS**)
-  Lightweight and efficient (pure C, minimal dependencies)


---

##  Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/binary-beater/study_timer.git
cd study_timer
```

### 2. Build the program

- On Linux:
```bash
gcc main.c -o study_timer
./study_timer
```

- On Windows:
```bash
gcc main.c -o study_timer.exe -lwinmm
study_timer.exe
```

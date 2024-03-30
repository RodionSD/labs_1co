#include <stdlib.h> // Подключение стандартной библиотеки для работы с памятью и функций стандартного ввода/вывода
#include <stdio.h> // Подключение стандартной библиотеки для работы с файлами
#include <string.h> // Подключение стандартной библиотеки для работы со строками

#define SIZE 256 // Определение макроса для размера строки

struct spisok { // Определение структуры узла списка
    char *top; // Указатель на слово
    struct spisok *next; // Указатель на следующий элемент списка
};

char *Dinam(char a[]) { // Функция для выделения динамической памяти и копирования строки
    char *copy = strdup(a); // Копирование строки 'a' и выделение памяти
    if (copy == NULL) { // Проверка на успешное выделение памяти
        printf("Память не выделена!\n"); // Вывод сообщения об ошибке
        exit(1); // Выход из программы с кодом ошибки
    }
    return copy; // Возврат указателя на новую копию строки
}

void delete(struct spisok *slovo) { // Функция для удаления одинаковых слов из списка
    struct spisok *current = slovo->next; // Указатель на первый элемент списка

    while (current != NULL) { // Пока не достигнут конец списка
        struct spisok *runner = current; // Указатель для прохода по оставшимся элементам

        while (runner->next != NULL) { // Пока не достигнут конец списка
            if (strcmp(current->top, runner->next->top) == 0) { // Если слова совпадают
                struct spisok *toFree = runner->next; // Запоминаем элемент для освобождения
                runner->next = runner->next->next; // Удаляем дубликат из списка
                free(toFree->top); // Освобождение памяти, занятой словом
                free(toFree); // Освобождение памяти, занятой узлом списка
            } else {
                runner = runner->next; // Переход к следующему элементу списка
            }
        }

        current = current->next; // Переход к следующему элементу списка
    }
}

void freeSpisok(struct spisok *head) { // Функция для освобождения памяти, занятой списком
    while (head != NULL) { // Пока не достигнут конец списка
        struct spisok *temp = head; // Запоминаем текущий элемент
        head = head->next; // Переход к следующему элементу списка
        free(temp->top); // Освобождение памяти, занятой словом
        free(temp); // Освобождение памяти, занятой узлом списка
    }
}

struct spisok *createSpisok() { // Функция для создания пустого списка
    struct spisok *head = (struct spisok *)malloc(sizeof(struct spisok)); // Выделение памяти под заголовок списка
    if (head == NULL) { // Проверка на успешное выделение памяти
        printf("Память не выделена!\n"); // Вывод сообщения об ошибке
        exit(1); // Выход из программы с кодом ошибки
    }
    head->top = Dinam(""); // Инициализация первого элемента пустой строкой
    head->next = NULL; // Указатель на следующий элемент равен NULL
    return head; // Возврат указателя на созданный список
}

void vfile(struct spisok *slovo, FILE *file) { // Функция для вывода списка в файл или на экран
    struct spisok *temp = slovo->next; // Указатель на первый элемент списка
    while (temp != NULL) { // Пока не достигнут конец списка
        fprintf(file, "%s\n", temp->top); // Вывод слова в файл или на экран
        temp = temp->next; // Переход к следующему элементу списка
    }
}

void izfile(struct spisok *evenList, struct spisok *oddList, FILE *inputFile, FILE *outputFile) {
    char buf[SIZE]; // Буфер для чтения слова из файла
    int order = 0; // Порядковый номер слова

    while (fscanf(inputFile, "%s", buf) != EOF) { // Чтение слова из файла до конца файла
        struct spisok *temp = order % 2 == 0 ? evenList : oddList; // Выбор списка для добавления слова

        while (temp->next != NULL) { // Пока не достигнут конец списка
            temp = temp->next; // Переход к следующему элементу списка
        }

        temp->next = (struct spisok *)malloc(sizeof(struct spisok)); // Выделение памяти под новый узел
        if (temp->next == NULL) { // Проверка на успешное выделение памяти
            printf("Память не выделена!\n"); // Вывод сообщения об ошибке
            exit(1); // Выход из программы с кодом ошибки
        }

        temp = temp->next; // Переход к новому узлу
        temp->top = Dinam(buf); // Запись слова в узел
        temp->next = NULL; // Установка указателя на следующий элемент равным NULL

        order++; // Увеличение порядкового номера
    }

    delete(evenList); // Удаление одинаковых слов в списках
    delete(oddList);
}

int main(int argc, char *argv[]) {
    if (argc != 3) { // Проверка на правильное количество аргументов командной строки
        printf("Неверное использование\n"); // Вывод сообщения об ошиб


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Неверное использование\n");
        printf("%s <входной_файл> <выходной_файл>\n", argv[0]);
        exit(1);
    }

    FILE *inputFile = fopen(argv[1], "r");

    if (inputFile == NULL) {
        printf("Не удалось открыть входной файл\n");
        exit(1);
    }

    FILE *outputFile = fopen(argv[2], "w");

    if (outputFile == NULL) {
        printf("Не удалось открыть выходной файл\n");
        fclose(inputFile);
        exit(1);
    }

    // Создание двух списков строк
    struct spisok *evenList = createSpisok();
    struct spisok *oddList = createSpisok();

    // Чтение данных из файла и заполнение списков
    izfile(evenList, oddList, inputFile, outputFile);

    vfile(evenList, stdout); // Вывод списка четных строк на экран
    vfile(oddList, outputFile); // Запись списка нечетных строк в выходной файл
    
    // Закрытие файлов
    fclose(inputFile);
    fclose(outputFile);
    
    // Освобождение памяти, выделенной под списки
    freeSpisok(evenList);
    freeSpisok(oddList);

    return 0;
}


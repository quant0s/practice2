#include <stdio.h>
#include <string.h>
#include <math.h>

void task18()
{
  FILE *file1, *file2, *result_file;
  int columns1, columns2, rows1 = 0, rows2 = 0;
  int matrix1[10][10], matrix2[10][10], matrix_result[10][10];

  result_file = fopen("D:/C/Code2/task18_result_file.txt", "w");

  if ((file1 = fopen("D:/C/Code2/task18_file1.txt", "r")) == NULL || (file2 = fopen("D:/C/Code2/task18_file2.txt", "r")) == NULL)
  {
    printf("Не удалось открыть файл\n");
    return;
  }

  fscanf(file1, "%d", &columns1);
  fscanf(file2, "%d", &columns2);

  while (!feof(file1)) 
  {
    for (int i = 0; i < columns1; i++)
    {
      fscanf(file1, "%d", &matrix1[rows1][i]);
    }
    rows1++;
  }

  while (!feof(file2)) 
  {
    for (int i = 0; i < columns2; i++)
    {
      fscanf(file2, "%d", &matrix2[rows2][i]);
    }
    rows2++;
  }

  if (columns1 != rows2)
  {
    printf("Матрицы нельзя так как количество столбцов первой матрицы не равно количеству строк второй матрицы (%d != %d)", columns1, rows2);
    return;
  }

  for (int i = 0; i < rows1; i++)
  {
    for (int j = 0; j < columns2; j++)
    {
      matrix_result[i][j] = 0;
      for (int k = 0; k < columns1; k++)
      {
        matrix_result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
      fprintf(result_file, "%d ", matrix_result[i][j]);
    }
    fprintf(result_file, "\n");
  }
  printf("Умножение матриц выполнено.\n");

  fclose(file1); 
  fclose(file2); 
  fclose(result_file);
}

void task19()
{
  FILE *in, *out;
  int size;
  int matrix[10][10] = {0};

  out = fopen("D:/C/Code2/task19_out.txt", "w");

  if ((in = fopen("D:/C/Code2/task19_in.txt", "r")) == NULL)
  {
    printf("Не удалось открыть файл\n");
    return;
  }

  fscanf(in, "%d", &size);

  for (int i = 0; i < size; i++)
  {
    for (int j = i; j < size; j++)
    {
      fscanf(in, "%d", &matrix[i][j]);
    }
  }

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      fprintf(out, "%d ", matrix[i][j]);
    }
    fprintf(out, "\n");
  }
  printf("Матрица восстановлена.\n");

  fclose(in);
  fclose(out);
}

void task20()
{
  FILE *file1, *file2, *help_file;
  char c;

  help_file = fopen("D:/C/Code2/task20_help_file.txt", "w");

  if ((file1 = fopen("D:/C/Code2/task20_file1.txt", "r")) == NULL || (file2 = fopen("D:/C/Code2/task20_file2.txt", "r")) == NULL)
  {
    printf("Не удалось открыть файл\n");
    return;
  }

  while ((c = fgetc(file1)) != EOF)
  {
    fputc(c, help_file);
  }

  fclose(file1);
  fclose(help_file);
  file1 = fopen("D:/C/Code2/task20_file1.txt", "w");

  while ((c = getc(file2)) != EOF)
  {
    fputc(c, file1);
  }

  fclose(file2);
  fclose(file1);
  file2 = fopen("D:/C/Code2/task20_file2.txt", "w");
  help_file = fopen("D:/C/Code2/task20_help_file.txt", "r");

  while ((c = getc(help_file)) != EOF)
  {
    fputc(c, file2);
  }
  printf("Файлы обменяны данными.\n");

  fclose(file2);
  fclose(help_file);
  remove("D:/C/Code2/task20_help_file.txt");
}

void task21()
{
  FILE *file;
  char line[100], longest[100] = "";
  int max_len = 0, number_line = 0, longest_number_line = 0;

  if ((file = fopen("D:/C/Code2/task21_file.txt", "r")) == NULL)
  {
    printf("Не удалось открыть файл\n");
    return;
  }

  while(fgets(line, 100, file))
  {
    number_line++;
    int len = strlen(line);
    if (line[len - 1] == '\n')
    {
      line[len - 1] = '\0';
      len--;
    }

    if (len > max_len)
    {
      max_len = len;
      strcpy(longest, line);
      longest_number_line = number_line;
    }
  }

  fclose(file);

  if (max_len > 0)
  {
    printf("Самая длинная строка - %d (длина %d):\n%s\n", longest_number_line, max_len, longest);
  }
  else
  {
    printf("Файл пуст\n");
  }
}

void task22()
{
  FILE *file;
  int num, count_square = 0;
  
  file = fopen("D:/C/Code2/task22_file.txt", "a+");
  
  fprintf(file, "\n");
  
  rewind(file);
  while (fscanf(file, "%d", &num) == 1) 
  {
    int temp = abs(num);
    int root = (int)sqrt(temp);
    int is_square = (root * root == temp);
    
    int len = 0;

    if (num <= 0) 
    {
      len++;
    }
    while (temp > 0) 
    {
      len++;
      temp /= 10;
    }
    
    long int current_pos = ftell(file);
    
    fseek(file, 0, SEEK_END);
    if (is_square) 
    {
      count_square++;
      for (int i = 0; i < len; i++) 
      {
        fprintf(file, "-");
      }
    } 
    else 
    {
      for (int i = 0; i < len; i++) 
      {
        fprintf(file, " ");
      }
    }
    fprintf(file, " ");
    fseek(file, current_pos, SEEK_SET);
  }
  
  fclose(file);
  printf("Подчеркивания добавлены в файл\n");
  printf("Количество чисел, которые являются точными квадратами: %d\n", count_square);
}

int main() 
{
  int choice;
  printf("Введите число для выбора номера задания (18-22) или 0 для выхода: ");
  scanf("%d", &choice);

  while (choice != 0)
  {
    switch (choice)
    {
      case 18: task18(); break;
      case 19: task19(); break;
      case 20: task20(); break;
      case 21: task21(); break;
      case 22: task22(); break;
      default: break;
    }
    printf("\nВведите число для выбора номера задания (18-22) или 0 для выхода: ");
    scanf("%d", &choice);
  }
  printf("Конец программы");
  return 0;
}
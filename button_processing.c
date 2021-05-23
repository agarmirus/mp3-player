// Вызов функции:
// int button[4];
// button_processing(button);
void button_processsing(int *const button)   // Да, пусть всё-таки функция будет принимать на вход массив флажков
{
    button[0] = digitalRead(D8) == HIGH ? 1 : 0;
    button[1] = digitalRead(D9) == HIGH ? 1 : 0;
    button[2] = digitalRead(D10) == HIGH ? 1 : 0;
    button[3] = digitalRead(D11) == HIGH ? 1 : 0;
}
struct student
// {
//   int num;
//   float score;
//   struct student *next;
// };

// int main()
// {
//   struct student *head, *p;
//   // 建立链表
//   head = p = (struct student)malloc(LEN); // 开辟一个新单元，让p和head指向它
//   scanf("%d, %f", &p->num, &p->score);    // 输入第一个结点的数据
//   p = (struct student *)malloc(LEN);      // 开辟第二个新单元，并让P指向他
//   scanf("%d,%f", &p->num, &p->score);     // 输入第二个结点的数据
//   head->next = p;                         // 使第1个结点中的next成员指向第二个结点
//   p->next = NULL;                         // 使第2个结点中的next成员不指向任何对象
//   // 输出两个结点中的数据
//   p = head;
//   printf("\n结点1：%d,%6.2f\n", p->num, p->score);
//   p = p->next;
//   printf("结点2：%d,%6.2f\n", p->num, p->score);
//   return 0;
// }

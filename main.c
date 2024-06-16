#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// 函数声明
void input();
void add();
void display();
void sort();
void search();
void statistics();
void clearConsole();
void updateEmployee();
int getMaxCardID();//取得当前最大卡号
void deleteWorkerByCardID();

// 定义员工结构体
struct Worker {
    int card_id;
    char name[12];
    char month[10];
    float basic_salary;
    float allowance;
    float subsidy;
    float gross_salary;
    float water_fee;
    float electricity_fee;
    float tax;
    float net_salary;
    struct Worker *next;
};


int main() {
    int choice, flag = 0;
    system("color F1");

    //循环结构，非0退出循环
    while (flag == 0) {

        //输出前先清除控制台内容
        clearConsole();
        printf("\n***************************** 欢迎使用员工工资管理系统 **************************\n");
        printf("\n------------------- 请选择操作:\n");
        printf("----- 输入工资信息: 按 1\n");
        printf("----- 添加工资信息: 按 2\n");
        printf("----- 浏览工资信息: 按 3\n");
        printf("----- 排序工资信息: 按 4\n");
        printf("----- 查询工资信息: 按 5\n");
        printf("----- 统计功能: 按 6\n");
        printf("----- 更改职工信息: 按 7\n");
        printf("----- 删除职工信息: 按 8\n");
        printf("----- 退出本系统: 按 9\n");
        printf("------------------ 请输入您的选择:\n");

        scanf("%d", &choice);

        //取得输入后清除控制台内容再输出选择内容
        clearConsole();

        //选择结构
        switch (choice) {
            case 1: input(); break;
            case 2: add(); break;
            case 3: display(); break;
            case 4: sort(); break;
            case 5: search(); break;
            case 6: statistics(); break;
            case 7: updateEmployee(); break;
            case 8: deleteWorkerByCardID(); break;
            case 9: return 0;
            default: break;
        }
        printf("(0) 继续操作   (1) 完成所有操作  \n请输入:");
        scanf("%d", &flag);
    }
    return 0;
}

// 添加工资信息功能实现
void input() {
    int i = 0, n, flag;
    struct Worker *phead, *ptail;
    FILE *fp;

    printf("(1) 创建新的员工工资信息文件     (2) 添加员工工资信息\n----- 请选择:");
    scanf("%d", &flag);
    if (flag == 1) {
        fp = fopen("salary.dat", "wb");  // 覆写，删除原有文件
    } else if (flag == 2) {
        fp = fopen("salary.dat", "ab");  // 追加，保留原文件
    }
    clearConsole();
    if (fp == NULL) {
        printf("无法打开文件!\n");
        return;
    }

    printf("请输入员工数:");
    scanf("%d", &n);

    // 输入第一个员工的信息
    phead = (struct Worker *)malloc(sizeof(struct Worker));
    printf("姓名: ");
    scanf("%s", phead->name);
    printf("月份(YYMM): ");
    scanf("%s", phead->month);
    printf("基本工资: ");
    scanf("%f", &phead->basic_salary);
    printf("津贴: ");
    scanf("%f", &phead->allowance);
    printf("补贴: ");
    scanf("%f", &phead->subsidy);
    printf("水费: ");
    scanf("%f", &phead->water_fee);
    printf("电费: ");
    scanf("%f", &phead->electricity_fee);
    printf("税金: ");
    scanf("%f", &phead->tax);

    // 计算应发工资和实发工资
    phead->gross_salary = phead->basic_salary + phead->allowance + phead->subsidy;
    phead->net_salary = phead->gross_salary - phead->water_fee - phead->electricity_fee - phead->tax;

    // 获取当前最大卡号
    int max_card_id = getMaxCardID();

    // 自动生成卡号
    phead->card_id = ++max_card_id;

    // 将信息写入文件
    fwrite(phead, sizeof(struct Worker), 1, fp);
    phead->next = NULL;
    ptail = phead;

    clearConsole();

    // 输入剩余员工的信息
    for (i = 1; i < n; i++) {
        ptail->next = (struct Worker *)malloc(sizeof(struct Worker));
        ptail = ptail->next;

        printf("姓名: ");
        scanf("%s", ptail->name);
        printf("月份(YYMM): ");
        scanf("%s", ptail->month);
        printf("基本工资: ");
        scanf("%f", &ptail->basic_salary);
        printf("津贴: ");
        scanf("%f", &ptail->allowance);
        printf("补贴: ");
        scanf("%f", &ptail->subsidy);
        printf("水费: ");
        scanf("%f", &ptail->water_fee);
        printf("电费: ");
        scanf("%f", &ptail->electricity_fee);
        printf("税金: ");
        scanf("%f", &ptail->tax);

        // 计算应发工资和实发工资
        ptail->gross_salary = ptail->basic_salary + ptail->allowance + ptail->subsidy;
        ptail->net_salary = ptail->gross_salary - ptail->water_fee - ptail->electricity_fee - ptail->tax;

        // 自动生成卡号
        ptail->card_id = ++max_card_id;

        // 将信息写入文件
        fwrite(ptail, sizeof(struct Worker), 1, fp);
        ptail->next = NULL;
        clearConsole();
    }

    fclose(fp);

    // 释放链表内存
    while (phead != NULL) {
        struct Worker *temp = phead;
        phead = phead->next;
        free(temp);
    }

    printf("员工信息录入成功!\n");
}



//添加工资信息实现,此模式默认为追加append，且人数默认1人
void add() {
    struct Worker worker;
    FILE *fp;
    int max_card_id;


    // 打开文件进行追加
    fp = fopen("salary.dat", "ab");
    if (fp == NULL) {
        printf("无法打开文件!\n");
        return;
    }

    // 输入工资信息
    printf("请输入工资信息:\n");
    printf("姓名: ");
    scanf("%s", worker.name);
    printf("月份(YYMM): ");
    scanf("%s", worker.month);
    printf("基本工资: ");
    scanf("%f", &worker.basic_salary);
    printf("津贴: ");
    scanf("%f", &worker.allowance);
    printf("补贴: ");
    scanf("%f", &worker.subsidy);
    printf("水费: ");
    scanf("%f", &worker.water_fee);
    printf("电费: ");
    scanf("%f", &worker.electricity_fee);
    printf("税金: ");
    scanf("%f", &worker.tax);

    // 计算应发工资和实发工资
    worker.gross_salary = worker.basic_salary + worker.allowance + worker.subsidy;
    worker.net_salary = worker.gross_salary - worker.water_fee - worker.electricity_fee - worker.tax;

    // 获取当前最大卡号
    max_card_id = getMaxCardID();

    // 自动生成卡号
    worker.card_id = ++max_card_id;

    // 写入信息到文件
    fwrite(&worker, sizeof(struct Worker), 1, fp);

    fclose(fp);

    printf("员工信息添加成功!\n");
}


// 浏览全部工资信息
void display() {
    struct Worker a;
    int i;
    FILE *fp = fopen("salary.dat", "rb");

    if (fp == NULL) {
        printf("文件不存在!\n");
        return;
    }

    // 判断文件是否为空
    fseek(fp, 0, SEEK_END);  // 将文件指针移到文件末尾
    if (ftell(fp) == 0) {
        printf("文件为空!\n");
        fclose(fp);
        return;
    }
    fseek(fp, 0, SEEK_SET);  // 将文件指针移到文件开头

    while (1) {
        for (i = 0; i < 10 && fread(&a, sizeof(struct Worker), 1, fp); i++) {
            printf("工资卡号: %d\t", a.card_id);
            printf("姓名: %s\t", a.name);
            printf("月份: %s\t", a.month);
            printf("基本工资: %.1f\t", a.basic_salary);
            printf("津贴: %.1f\t", a.allowance);
            printf("补贴: %.1f\n", a.subsidy);
            printf("应发工资: %.1f\t", a.gross_salary);
            printf("水费: %.1f\t", a.water_fee);
            printf("电费: %.1f\t", a.electricity_fee);
            printf("税金: %.1f\t", a.tax);
            printf("实发工资: %.1f\n\n", a.net_salary);
        }

        if (i < 10) break;
        printf("按任意键显示下一页...");
        getchar();
        getchar();  // 消耗多余的换行符
    }

    fclose(fp);
}



//排序操作
void sort() {
    int choice, i, j;
    struct Worker *workers = NULL, temp;
    int count = 0;

    FILE *fp = fopen("salary.dat", "rb");

    //找不到文件报错
    if (!fp) {
        printf("无法打开文件!\n");
        return;
    }

    // 计数记录
    while (fread(&temp, sizeof(struct Worker), 1, fp)) {
        count++;
    }
    rewind(fp);

    // 提前申请内存
    workers = (struct Worker *)malloc(count * sizeof(struct Worker));
    for (i = 0; i < count; i++) {
        fread(&workers[i], sizeof(struct Worker), 1, fp);
    }
    fclose(fp);

    printf("请选择排序方式:\n");
    printf("1. 按工资卡号升序\n");
    printf("2. 按实发工资降序\n");
    printf("3. 按姓名字典序\n");
    printf("请输入您的选择: ");
    scanf("%d", &choice);

    // 排序实现
    switch (choice) {
        case 1:
            for (i = 0; i < count - 1; i++) {
                for (j = 0; j < count - i - 1; j++) {
                    if (workers[j].card_id > workers[j + 1].card_id) {
                        temp = workers[j];
                        workers[j] = workers[j + 1];
                        workers[j + 1] = temp;
                    }
                }
            }
            break;
        case 2:
            for (i = 0; i < count - 1; i++) {
                for (j = 0; j < count - i - 1; j++) {
                    if (workers[j].net_salary < workers[j + 1].net_salary) {
                        temp = workers[j];
                        workers[j] = workers[j + 1];
                        workers[j + 1] = temp;
                    }
                }
            }
            break;
        case 3:
            for (i = 0; i < count - 1; i++) {
                for (j = 0; j < count - i - 1; j++) {
                    if (strcmp(workers[j].name, workers[j + 1].name) > 0) {
                        temp = workers[j];
                        workers[j] = workers[j + 1];
                        workers[j + 1] = temp;
                    }
                }
            }
            break;
        default:
            printf("无效选择!\n");
            free(workers);
            return;
    }

    // 将排好的数据重新写入
    fp = fopen("salary.dat", "wb");
    for (i = 0; i < count; i++) {
        fwrite(&workers[i], sizeof(struct Worker), 1, fp);
    }
    fclose(fp);
    free(workers);

    printf("排序完成!\n");
}

//查找功能实现
void search() {
    int choice, card_id;
    char name[12];
    struct Worker a;
    FILE *fp = fopen("salary.dat", "rb");
    int found = 0;

    printf("请选择查询条件:\n");
    printf("1. 按工资卡号\n");
    printf("2. 按姓名\n");
    printf("请输入您的选择: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("请输入工资卡号: ");
            scanf("%d", &card_id);
            while (fread(&a, sizeof(struct Worker), 1, fp)) {
                if (a.card_id == card_id) {
                    printf("工资卡号: %d\t姓名: %s\t月份: %s\t基本工资: %.1f\t津贴: %.1f\t补贴: %.1f\n应发工资: %.1f\t水费: %.1f\t电费: %.1f\t税金: %.1f\t实发工资: %.1f\n",
                           a.card_id, a.name, a.month, a.basic_salary, a.allowance, a.subsidy, a.gross_salary, a.water_fee, a.electricity_fee, a.tax, a.net_salary);
                    found = 1;
                }
            }
            break;
        case 2:
            printf("请输入姓名: ");
            scanf("%s", name);
            while (fread(&a, sizeof(struct Worker), 1, fp)) {
                if (strcmp(a.name, name) == 0) {
                    printf("工资卡号: %d\t姓名: %s\t月份: %s\t基本工资: %.1f\t津贴: %.1f\t补贴: %.1f\n应发工资: %.1f\t水费: %.1f\t电费: %.1f\t税金: %.1f\t实发工资: %.1f\n",
                           a.card_id, a.name, a.month, a.basic_salary, a.allowance, a.subsidy, a.gross_salary, a.water_fee, a.electricity_fee, a.tax, a.net_salary);
                    found = 1;
                }
            }
            break;
        default:
            printf("无效选择!\n");
            fclose(fp);
            return;
    }

    if (!found) {
        printf("未找到匹配的记录!\n");
    }

    fclose(fp);
}

//统计功能实现
void statistics() {
    int start_month, end_month, i;
    float total_net_salary = 0.0;
    struct Worker a;
    FILE *fp = fopen("salary.dat", "rb");

    if (!fp) {
        printf("无法打开文件!\n");
        return;
    }

    printf("请输入起始月份 (格式为 YYYYMM): ");
    scanf("%d", &start_month);
    printf("请输入结束月份 (格式为 YYYYMM): ");
    scanf("%d", &end_month);

    while (fread(&a, sizeof(struct Worker), 1, fp)) {
        int record_month = atoi(a.month);  // 假设月份是以字符串格式保存的，格式为 "YYYYMM"
        if (record_month >= start_month && record_month <= end_month) {
            total_net_salary += a.net_salary;
        }
    }

    fclose(fp);

    printf("从 %d 到 %d 的实发工资总额为: %.2f\n", start_month, end_month, total_net_salary);
}

//更新信息功能实现
void updateEmployee() {
    int choice, card_id, found_count = 0;
    char name[12];
    struct Worker a;
    FILE *fp;
    struct Worker found_worker;
    long int pos;

    printf("请选择查找方式:\n");
    printf("1. 按工资卡号\n");
    printf("2. 按姓名\n");
    printf("请输入您的选择: ");
    scanf("%d", &choice);

    fp = fopen("salary.dat", "rb+");
    if (!fp) {
        printf("无法打开文件!\n");
        return;
    }

    switch (choice) {
        case 1:
            printf("请输入工资卡号: ");
            scanf("%d", &card_id);
            while (fread(&a, sizeof(struct Worker), 1, fp)) {
                if (a.card_id == card_id) {
                    found_worker = a;
                    found_count++;
                    pos = ftell(fp) - sizeof(struct Worker);
                }
            }
            break;
        case 2:
            printf("请输入姓名: ");
            scanf("%s", name);
            while (fread(&a, sizeof(struct Worker), 1, fp)) {
                if (strcmp(a.name, name) == 0) {
                    found_worker = a;
                    found_count++;
                    pos = ftell(fp) - sizeof(struct Worker);
                }
            }
            break;
        default:
            printf("无效选择!\n");
            fclose(fp);
            return;
    }

    if (found_count == 0) {
        printf("未找到匹配的记录!\n");
    } else if (found_count > 1) {
        printf("找到多个匹配的记录，请更准确地提供查询条件!\n");
    } else {
        printf("找到的员工信息:\n");
        printf("姓名: %s\t月份: %s\t基本工资: %.1f\t津贴: %.1f\t补贴: %.1f\n应发工资: %.1f\t水费: %.1f\t电费: %.1f\t税金: %.1f\t实发工资: %.1f\n",
               found_worker.name, found_worker.month, found_worker.basic_salary, found_worker.allowance, found_worker.subsidy,
               found_worker.gross_salary, found_worker.water_fee, found_worker.electricity_fee, found_worker.tax, found_worker.net_salary);

        printf("请输入更新后的信息 (除工资卡号外):\n");
        printf("姓名: ");
        scanf("%s", found_worker.name);
        printf("月份: ");
        scanf("%s", found_worker.month);
        printf("基本工资: ");
        scanf("%f", &found_worker.basic_salary);
        printf("津贴: ");
        scanf("%f", &found_worker.allowance);
        printf("补贴: ");
        scanf("%f", &found_worker.subsidy);
        printf("水费: ");
        scanf("%f", &found_worker.water_fee);
        printf("电费: ");
        scanf("%f", &found_worker.electricity_fee);
        printf("税金: ");
        scanf("%f", &found_worker.tax);

        // 计算应发工资和实发工资
        found_worker.gross_salary = found_worker.basic_salary + found_worker.allowance + found_worker.subsidy;
        found_worker.net_salary = found_worker.gross_salary - found_worker.water_fee - found_worker.electricity_fee - found_worker.tax;

        fseek(fp, pos, SEEK_SET);
        fwrite(&found_worker, sizeof(struct Worker), 1, fp);
        printf("信息更新成功!\n");
    }

    fclose(fp);
}


//清空控制台输出
void clearConsole() {
    // Windows系统
#ifdef _WIN32
    system("cls");
#else
    // Unix/Linux/MacOS系统
    system("clear");
#endif
}

int getMaxCardID() {
    struct Worker worker;
    FILE *fp;
    int max_card_id = 0;  // 初始化为0
    int record_count = 0; // 用于记录文件中的记录数量

    fp = fopen("salary.dat", "rb");
    if (fp == NULL) {
        return max_card_id;  // 如果文件不存在，直接返回0
    }

    // 检测文件是否为空
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        fclose(fp);
        return max_card_id;  // 文件为空，返回0
    }
    rewind(fp);  // 将文件指针重新指向文件开头

    // 遍历文件中的每个记录，找到最大的卡号
    while (fread(&worker, sizeof(struct Worker), 1, fp)) {
        record_count++;
        if (worker.card_id > max_card_id) {
            max_card_id = worker.card_id;
        }
    }

    fclose(fp);

    // 如果记录数少于等于1，返回0
    if (record_count < 1) {
        return 0;
    }
    return max_card_id;
}


void deleteWorkerByCardID() {
    int card_id;
    struct Worker worker;
    FILE *fp, *fp_temp;
    int found = 0; // 用于标记是否找到要删除的记录

    printf("请输入要删除的员工工资卡号: ");
    scanf("%d", &card_id);

    // 打开原始文件读取数据
    fp = fopen("salary.dat", "rb");
    if (fp == NULL) {
        printf("工资数据文件不存在。\n");
        return;
    }

    // 打开临时文件，用于存储删除记录后的数据
    fp_temp = fopen("temp.dat", "wb");
    if (fp_temp == NULL) {
        printf("无法创建临时文件。\n");
        fclose(fp);
        return;
    }

    // 遍历原始文件中的每个记录
    while (fread(&worker, sizeof(struct Worker), 1, fp)) {
        // 如果当前记录的卡号与要删除的卡号不一致，写入临时文件
        if (worker.card_id != card_id) {
            fwrite(&worker, sizeof(struct Worker), 1, fp_temp);
        } else {
            found = 1; // 标记找到要删除的记录
        }
    }

    fclose(fp);
    fclose(fp_temp);

    // 如果找到了要删除的记录，替换原始文件
    if (found) {
        remove("salary.dat");       // 删除原始文件
        rename("temp.dat", "salary.dat"); // 将临时文件重命名为原始文件名
        printf("工资卡号为 %d 的员工信息已删除。\n", card_id);
    } else {
        remove("temp.dat"); // 删除临时文件
        printf("未找到工资卡号为 %d 的员工信息。\n", card_id);
    }
}
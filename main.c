#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// ��������
void input();
void add();
void display();
void sort();
void search();
void statistics();
void clearConsole();
void updateEmployee();
int getMaxCardID();//ȡ�õ�ǰ��󿨺�
void deleteWorkerByCardID();

// ����Ա���ṹ��
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

    //ѭ���ṹ����0�˳�ѭ��
    while (flag == 0) {

        //���ǰ���������̨����
        clearConsole();
        printf("\n***************************** ��ӭʹ��Ա�����ʹ���ϵͳ **************************\n");
        printf("\n------------------- ��ѡ�����:\n");
        printf("----- ���빤����Ϣ: �� 1\n");
        printf("----- ��ӹ�����Ϣ: �� 2\n");
        printf("----- ���������Ϣ: �� 3\n");
        printf("----- ��������Ϣ: �� 4\n");
        printf("----- ��ѯ������Ϣ: �� 5\n");
        printf("----- ͳ�ƹ���: �� 6\n");
        printf("----- ����ְ����Ϣ: �� 7\n");
        printf("----- ɾ��ְ����Ϣ: �� 8\n");
        printf("----- �˳���ϵͳ: �� 9\n");
        printf("------------------ ����������ѡ��:\n");

        scanf("%d", &choice);

        //ȡ��������������̨���������ѡ������
        clearConsole();

        //ѡ��ṹ
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
        printf("(0) ��������   (1) ������в���  \n������:");
        scanf("%d", &flag);
    }
    return 0;
}

// ��ӹ�����Ϣ����ʵ��
void input() {
    int i = 0, n, flag;
    struct Worker *phead, *ptail;
    FILE *fp;

    printf("(1) �����µ�Ա��������Ϣ�ļ�     (2) ���Ա��������Ϣ\n----- ��ѡ��:");
    scanf("%d", &flag);
    if (flag == 1) {
        fp = fopen("salary.dat", "wb");  // ��д��ɾ��ԭ���ļ�
    } else if (flag == 2) {
        fp = fopen("salary.dat", "ab");  // ׷�ӣ�����ԭ�ļ�
    }
    clearConsole();
    if (fp == NULL) {
        printf("�޷����ļ�!\n");
        return;
    }

    printf("������Ա����:");
    scanf("%d", &n);

    // �����һ��Ա������Ϣ
    phead = (struct Worker *)malloc(sizeof(struct Worker));
    printf("����: ");
    scanf("%s", phead->name);
    printf("�·�(YYMM): ");
    scanf("%s", phead->month);
    printf("��������: ");
    scanf("%f", &phead->basic_salary);
    printf("����: ");
    scanf("%f", &phead->allowance);
    printf("����: ");
    scanf("%f", &phead->subsidy);
    printf("ˮ��: ");
    scanf("%f", &phead->water_fee);
    printf("���: ");
    scanf("%f", &phead->electricity_fee);
    printf("˰��: ");
    scanf("%f", &phead->tax);

    // ����Ӧ�����ʺ�ʵ������
    phead->gross_salary = phead->basic_salary + phead->allowance + phead->subsidy;
    phead->net_salary = phead->gross_salary - phead->water_fee - phead->electricity_fee - phead->tax;

    // ��ȡ��ǰ��󿨺�
    int max_card_id = getMaxCardID();

    // �Զ����ɿ���
    phead->card_id = ++max_card_id;

    // ����Ϣд���ļ�
    fwrite(phead, sizeof(struct Worker), 1, fp);
    phead->next = NULL;
    ptail = phead;

    clearConsole();

    // ����ʣ��Ա������Ϣ
    for (i = 1; i < n; i++) {
        ptail->next = (struct Worker *)malloc(sizeof(struct Worker));
        ptail = ptail->next;

        printf("����: ");
        scanf("%s", ptail->name);
        printf("�·�(YYMM): ");
        scanf("%s", ptail->month);
        printf("��������: ");
        scanf("%f", &ptail->basic_salary);
        printf("����: ");
        scanf("%f", &ptail->allowance);
        printf("����: ");
        scanf("%f", &ptail->subsidy);
        printf("ˮ��: ");
        scanf("%f", &ptail->water_fee);
        printf("���: ");
        scanf("%f", &ptail->electricity_fee);
        printf("˰��: ");
        scanf("%f", &ptail->tax);

        // ����Ӧ�����ʺ�ʵ������
        ptail->gross_salary = ptail->basic_salary + ptail->allowance + ptail->subsidy;
        ptail->net_salary = ptail->gross_salary - ptail->water_fee - ptail->electricity_fee - ptail->tax;

        // �Զ����ɿ���
        ptail->card_id = ++max_card_id;

        // ����Ϣд���ļ�
        fwrite(ptail, sizeof(struct Worker), 1, fp);
        ptail->next = NULL;
        clearConsole();
    }

    fclose(fp);

    // �ͷ������ڴ�
    while (phead != NULL) {
        struct Worker *temp = phead;
        phead = phead->next;
        free(temp);
    }

    printf("Ա����Ϣ¼��ɹ�!\n");
}



//��ӹ�����Ϣʵ��,��ģʽĬ��Ϊ׷��append��������Ĭ��1��
void add() {
    struct Worker worker;
    FILE *fp;
    int max_card_id;


    // ���ļ�����׷��
    fp = fopen("salary.dat", "ab");
    if (fp == NULL) {
        printf("�޷����ļ�!\n");
        return;
    }

    // ���빤����Ϣ
    printf("�����빤����Ϣ:\n");
    printf("����: ");
    scanf("%s", worker.name);
    printf("�·�(YYMM): ");
    scanf("%s", worker.month);
    printf("��������: ");
    scanf("%f", &worker.basic_salary);
    printf("����: ");
    scanf("%f", &worker.allowance);
    printf("����: ");
    scanf("%f", &worker.subsidy);
    printf("ˮ��: ");
    scanf("%f", &worker.water_fee);
    printf("���: ");
    scanf("%f", &worker.electricity_fee);
    printf("˰��: ");
    scanf("%f", &worker.tax);

    // ����Ӧ�����ʺ�ʵ������
    worker.gross_salary = worker.basic_salary + worker.allowance + worker.subsidy;
    worker.net_salary = worker.gross_salary - worker.water_fee - worker.electricity_fee - worker.tax;

    // ��ȡ��ǰ��󿨺�
    max_card_id = getMaxCardID();

    // �Զ����ɿ���
    worker.card_id = ++max_card_id;

    // д����Ϣ���ļ�
    fwrite(&worker, sizeof(struct Worker), 1, fp);

    fclose(fp);

    printf("Ա����Ϣ��ӳɹ�!\n");
}


// ���ȫ��������Ϣ
void display() {
    struct Worker a;
    int i;
    FILE *fp = fopen("salary.dat", "rb");

    if (fp == NULL) {
        printf("�ļ�������!\n");
        return;
    }

    // �ж��ļ��Ƿ�Ϊ��
    fseek(fp, 0, SEEK_END);  // ���ļ�ָ���Ƶ��ļ�ĩβ
    if (ftell(fp) == 0) {
        printf("�ļ�Ϊ��!\n");
        fclose(fp);
        return;
    }
    fseek(fp, 0, SEEK_SET);  // ���ļ�ָ���Ƶ��ļ���ͷ

    while (1) {
        for (i = 0; i < 10 && fread(&a, sizeof(struct Worker), 1, fp); i++) {
            printf("���ʿ���: %d\t", a.card_id);
            printf("����: %s\t", a.name);
            printf("�·�: %s\t", a.month);
            printf("��������: %.1f\t", a.basic_salary);
            printf("����: %.1f\t", a.allowance);
            printf("����: %.1f\n", a.subsidy);
            printf("Ӧ������: %.1f\t", a.gross_salary);
            printf("ˮ��: %.1f\t", a.water_fee);
            printf("���: %.1f\t", a.electricity_fee);
            printf("˰��: %.1f\t", a.tax);
            printf("ʵ������: %.1f\n\n", a.net_salary);
        }

        if (i < 10) break;
        printf("���������ʾ��һҳ...");
        getchar();
        getchar();  // ���Ķ���Ļ��з�
    }

    fclose(fp);
}



//�������
void sort() {
    int choice, i, j;
    struct Worker *workers = NULL, temp;
    int count = 0;

    FILE *fp = fopen("salary.dat", "rb");

    //�Ҳ����ļ�����
    if (!fp) {
        printf("�޷����ļ�!\n");
        return;
    }

    // ������¼
    while (fread(&temp, sizeof(struct Worker), 1, fp)) {
        count++;
    }
    rewind(fp);

    // ��ǰ�����ڴ�
    workers = (struct Worker *)malloc(count * sizeof(struct Worker));
    for (i = 0; i < count; i++) {
        fread(&workers[i], sizeof(struct Worker), 1, fp);
    }
    fclose(fp);

    printf("��ѡ������ʽ:\n");
    printf("1. �����ʿ�������\n");
    printf("2. ��ʵ�����ʽ���\n");
    printf("3. �������ֵ���\n");
    printf("����������ѡ��: ");
    scanf("%d", &choice);

    // ����ʵ��
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
            printf("��Чѡ��!\n");
            free(workers);
            return;
    }

    // ���źõ���������д��
    fp = fopen("salary.dat", "wb");
    for (i = 0; i < count; i++) {
        fwrite(&workers[i], sizeof(struct Worker), 1, fp);
    }
    fclose(fp);
    free(workers);

    printf("�������!\n");
}

//���ҹ���ʵ��
void search() {
    int choice, card_id;
    char name[12];
    struct Worker a;
    FILE *fp = fopen("salary.dat", "rb");
    int found = 0;

    printf("��ѡ���ѯ����:\n");
    printf("1. �����ʿ���\n");
    printf("2. ������\n");
    printf("����������ѡ��: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("�����빤�ʿ���: ");
            scanf("%d", &card_id);
            while (fread(&a, sizeof(struct Worker), 1, fp)) {
                if (a.card_id == card_id) {
                    printf("���ʿ���: %d\t����: %s\t�·�: %s\t��������: %.1f\t����: %.1f\t����: %.1f\nӦ������: %.1f\tˮ��: %.1f\t���: %.1f\t˰��: %.1f\tʵ������: %.1f\n",
                           a.card_id, a.name, a.month, a.basic_salary, a.allowance, a.subsidy, a.gross_salary, a.water_fee, a.electricity_fee, a.tax, a.net_salary);
                    found = 1;
                }
            }
            break;
        case 2:
            printf("����������: ");
            scanf("%s", name);
            while (fread(&a, sizeof(struct Worker), 1, fp)) {
                if (strcmp(a.name, name) == 0) {
                    printf("���ʿ���: %d\t����: %s\t�·�: %s\t��������: %.1f\t����: %.1f\t����: %.1f\nӦ������: %.1f\tˮ��: %.1f\t���: %.1f\t˰��: %.1f\tʵ������: %.1f\n",
                           a.card_id, a.name, a.month, a.basic_salary, a.allowance, a.subsidy, a.gross_salary, a.water_fee, a.electricity_fee, a.tax, a.net_salary);
                    found = 1;
                }
            }
            break;
        default:
            printf("��Чѡ��!\n");
            fclose(fp);
            return;
    }

    if (!found) {
        printf("δ�ҵ�ƥ��ļ�¼!\n");
    }

    fclose(fp);
}

//ͳ�ƹ���ʵ��
void statistics() {
    int start_month, end_month, i;
    float total_net_salary = 0.0;
    struct Worker a;
    FILE *fp = fopen("salary.dat", "rb");

    if (!fp) {
        printf("�޷����ļ�!\n");
        return;
    }

    printf("��������ʼ�·� (��ʽΪ YYYYMM): ");
    scanf("%d", &start_month);
    printf("����������·� (��ʽΪ YYYYMM): ");
    scanf("%d", &end_month);

    while (fread(&a, sizeof(struct Worker), 1, fp)) {
        int record_month = atoi(a.month);  // �����·������ַ�����ʽ����ģ���ʽΪ "YYYYMM"
        if (record_month >= start_month && record_month <= end_month) {
            total_net_salary += a.net_salary;
        }
    }

    fclose(fp);

    printf("�� %d �� %d ��ʵ�������ܶ�Ϊ: %.2f\n", start_month, end_month, total_net_salary);
}

//������Ϣ����ʵ��
void updateEmployee() {
    int choice, card_id, found_count = 0;
    char name[12];
    struct Worker a;
    FILE *fp;
    struct Worker found_worker;
    long int pos;

    printf("��ѡ����ҷ�ʽ:\n");
    printf("1. �����ʿ���\n");
    printf("2. ������\n");
    printf("����������ѡ��: ");
    scanf("%d", &choice);

    fp = fopen("salary.dat", "rb+");
    if (!fp) {
        printf("�޷����ļ�!\n");
        return;
    }

    switch (choice) {
        case 1:
            printf("�����빤�ʿ���: ");
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
            printf("����������: ");
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
            printf("��Чѡ��!\n");
            fclose(fp);
            return;
    }

    if (found_count == 0) {
        printf("δ�ҵ�ƥ��ļ�¼!\n");
    } else if (found_count > 1) {
        printf("�ҵ����ƥ��ļ�¼�����׼ȷ���ṩ��ѯ����!\n");
    } else {
        printf("�ҵ���Ա����Ϣ:\n");
        printf("����: %s\t�·�: %s\t��������: %.1f\t����: %.1f\t����: %.1f\nӦ������: %.1f\tˮ��: %.1f\t���: %.1f\t˰��: %.1f\tʵ������: %.1f\n",
               found_worker.name, found_worker.month, found_worker.basic_salary, found_worker.allowance, found_worker.subsidy,
               found_worker.gross_salary, found_worker.water_fee, found_worker.electricity_fee, found_worker.tax, found_worker.net_salary);

        printf("��������º����Ϣ (�����ʿ�����):\n");
        printf("����: ");
        scanf("%s", found_worker.name);
        printf("�·�: ");
        scanf("%s", found_worker.month);
        printf("��������: ");
        scanf("%f", &found_worker.basic_salary);
        printf("����: ");
        scanf("%f", &found_worker.allowance);
        printf("����: ");
        scanf("%f", &found_worker.subsidy);
        printf("ˮ��: ");
        scanf("%f", &found_worker.water_fee);
        printf("���: ");
        scanf("%f", &found_worker.electricity_fee);
        printf("˰��: ");
        scanf("%f", &found_worker.tax);

        // ����Ӧ�����ʺ�ʵ������
        found_worker.gross_salary = found_worker.basic_salary + found_worker.allowance + found_worker.subsidy;
        found_worker.net_salary = found_worker.gross_salary - found_worker.water_fee - found_worker.electricity_fee - found_worker.tax;

        fseek(fp, pos, SEEK_SET);
        fwrite(&found_worker, sizeof(struct Worker), 1, fp);
        printf("��Ϣ���³ɹ�!\n");
    }

    fclose(fp);
}


//��տ���̨���
void clearConsole() {
    // Windowsϵͳ
#ifdef _WIN32
    system("cls");
#else
    // Unix/Linux/MacOSϵͳ
    system("clear");
#endif
}

int getMaxCardID() {
    struct Worker worker;
    FILE *fp;
    int max_card_id = 0;  // ��ʼ��Ϊ0
    int record_count = 0; // ���ڼ�¼�ļ��еļ�¼����

    fp = fopen("salary.dat", "rb");
    if (fp == NULL) {
        return max_card_id;  // ����ļ������ڣ�ֱ�ӷ���0
    }

    // ����ļ��Ƿ�Ϊ��
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        fclose(fp);
        return max_card_id;  // �ļ�Ϊ�գ�����0
    }
    rewind(fp);  // ���ļ�ָ������ָ���ļ���ͷ

    // �����ļ��е�ÿ����¼���ҵ����Ŀ���
    while (fread(&worker, sizeof(struct Worker), 1, fp)) {
        record_count++;
        if (worker.card_id > max_card_id) {
            max_card_id = worker.card_id;
        }
    }

    fclose(fp);

    // �����¼�����ڵ���1������0
    if (record_count < 1) {
        return 0;
    }
    return max_card_id;
}


void deleteWorkerByCardID() {
    int card_id;
    struct Worker worker;
    FILE *fp, *fp_temp;
    int found = 0; // ���ڱ���Ƿ��ҵ�Ҫɾ���ļ�¼

    printf("������Ҫɾ����Ա�����ʿ���: ");
    scanf("%d", &card_id);

    // ��ԭʼ�ļ���ȡ����
    fp = fopen("salary.dat", "rb");
    if (fp == NULL) {
        printf("���������ļ������ڡ�\n");
        return;
    }

    // ����ʱ�ļ������ڴ洢ɾ����¼�������
    fp_temp = fopen("temp.dat", "wb");
    if (fp_temp == NULL) {
        printf("�޷�������ʱ�ļ���\n");
        fclose(fp);
        return;
    }

    // ����ԭʼ�ļ��е�ÿ����¼
    while (fread(&worker, sizeof(struct Worker), 1, fp)) {
        // �����ǰ��¼�Ŀ�����Ҫɾ���Ŀ��Ų�һ�£�д����ʱ�ļ�
        if (worker.card_id != card_id) {
            fwrite(&worker, sizeof(struct Worker), 1, fp_temp);
        } else {
            found = 1; // ����ҵ�Ҫɾ���ļ�¼
        }
    }

    fclose(fp);
    fclose(fp_temp);

    // ����ҵ���Ҫɾ���ļ�¼���滻ԭʼ�ļ�
    if (found) {
        remove("salary.dat");       // ɾ��ԭʼ�ļ�
        rename("temp.dat", "salary.dat"); // ����ʱ�ļ�������Ϊԭʼ�ļ���
        printf("���ʿ���Ϊ %d ��Ա����Ϣ��ɾ����\n", card_id);
    } else {
        remove("temp.dat"); // ɾ����ʱ�ļ�
        printf("δ�ҵ����ʿ���Ϊ %d ��Ա����Ϣ��\n", card_id);
    }
}
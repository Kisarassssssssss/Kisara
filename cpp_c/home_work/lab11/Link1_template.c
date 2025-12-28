#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// 歌曲节点结构体
typedef struct Song {
    int id;
    char title[100];
    char artist[50];
    char filepath[300];
    struct Song* next;
} Song;

// 播放列表管理器
typedef struct PlaylistManager{
    Song* head;
    Song* tail;
    Song* current;
    int song_count;
} PlaylistManager;

// 函数声明
void init_playlist_manager(PlaylistManager* manager);                           // 初始化链表
int load_songs_from_file(PlaylistManager* manager, const char* filename);       // 从文件中读取到链表
void add_song(PlaylistManager* manager, const char* title, const char* artist,  // 人工增加音乐
                const char* filepath);
void display_playlist(PlaylistManager* manager);                                // 显示播放列表
int delete_songs_by_title(PlaylistManager* manager, const char* title);         // 删除指定名字的音乐
int play_song_by_title(PlaylistManager* manager, const char* title);            // 根据名字播放音乐
int export_playlist(PlaylistManager* manager, const char* filename);            // 导出播放列表
int play_song_random(PlaylistManager* manager);                                 // 随机播放音乐
int insert_song_at(PlaylistManager* manager, int position, const char* title, const char* artist, const char* filepath);    // 向指定位置添加音乐
void destroy_playlist(PlaylistManager* manager);                                // 清空列表

// linux/Mac 版本
// void play_audio(const char* filename) {
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Founded File!!");
//     }
//     snprintf(command, sizeof(command), "afplay \"%s\"", filename);
//     int ret = system(command);
//     if (ret != 0) {
//         printf("播放失败或中断，请检查文件格式是否支持。\n");
//     }
// }

// Windows 版本
void play_audio(const char* filename){
    char command[256];
    FILE *mp3File = fopen(filename, "rb");
    if (!mp3File) {
        printf("无法打开文件 %s\n", filename);
        return;
    }
    else{
        printf("Founded File!!");
    }
    snprintf(command, sizeof(command), "start \"\" \"%s\"", filename);
    int ret = system(command);
    if (ret != 0) {
        printf("播放失败或中断，请检查文件格式是否支持。\n");
    }
    
    // 或者使用 Windows Media Player
    // sprintf(command, "wmplayer \"%s\"", filename);
    // system(command);
}


int load_songs_from_file(PlaylistManager* manager, const char* filename){
    FILE *fp=fopen(filename,"r");
    if (fp==NULL) {
        printf("Failed to open file\n");
        return -1; 
    }
    char name[100],artist[50],filepath[300];
    while(fscanf(fp,"%99[^,],%49[^,],%299s", name, artist, filepath) == 3)
    {
        Song *newsong=(Song*)malloc(sizeof(Song));
        manager->song_count++;
        newsong->id=manager->song_count;
        strcpy(newsong->title,name);
        strcpy(newsong->artist,artist);
        strcpy(newsong->filepath,filepath);
        newsong->next=NULL;
        if(manager->song_count==1)
        {
            manager->head=newsong;
            manager->tail=newsong;
            continue;
        }
        manager->tail->next=newsong;
        manager->tail=newsong;
    }
    fclose(fp);
    if(manager->song_count!=0)
    return manager->song_count;
    return 0;
}


// 初始化播放管理器
void init_playlist_manager(PlaylistManager* manager){
    manager->head = NULL;
    manager->tail = NULL;
    manager->current = NULL;
    manager->song_count = 0;
}
void idupdate(PlaylistManager *manager)
{
    if(manager->song_count==0)
    return;
    Song *tmp=manager->head;
    int num=1;
    while(tmp!=NULL)
    {
        tmp->id=num++;
        tmp = tmp->next; 
    }
}
// 1. 在链表末尾添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, 
            const char* filepath) {
                Song *newsong=(Song*)malloc(sizeof(Song));
                manager->song_count++;
                newsong->id=manager->song_count;
                newsong->next=NULL;
                strcpy(newsong->title,title);
                strcpy(newsong->artist,artist);
                strcpy(newsong->filepath,filepath);
                if(manager->head==NULL&&manager->tail==NULL)
                {
                    manager->head=newsong;
                    manager->tail=newsong;
                }
                else
                {
                    manager->tail->next=newsong;
                    manager->tail=newsong;
                }
                idupdate(manager);
                export_playlist(manager,"song_list_result.txt");
}

// 2. 显示播放列表
void display_playlist(PlaylistManager* manager) {
    if(manager->head==NULL)
    return;
    Song *tmp=manager->head;
    while(tmp!=NULL)
    {
        printf("%s %s %s\n",tmp->title,tmp->artist,tmp->filepath);
        tmp=tmp->next;
    }
    return;
}

// 3. 删除歌曲
int delete_songs_by_title(PlaylistManager* manager, const char* title) {
    if(manager->head==NULL)
    return 0;
    if(manager->head==manager->tail&&(strcmp(title,manager->head->title)==0))
    {
        Song *t=manager->head;
        free(t);
        manager->head=NULL;
        manager->tail=NULL;
        manager->song_count--;
        return 1;
    }
    Song *tmp=manager->head;
    Song *pre=NULL;    
    int sum=0;
    while(tmp!=NULL)
    {
        if(strcmp(title,tmp->title)==0)
        {
            if(tmp==manager->head)
            {
                manager->head=manager->head->next;
                free(tmp);
                tmp=manager->head;
                sum++;
                manager->song_count--;
            }
            else if(tmp==manager->tail)
            {
                sum++;
                manager->tail=pre;
                manager->tail->next=NULL;
                free(tmp);
                tmp=manager->tail;
                manager->song_count--;
            }
            else
            {
                sum++;
                pre->next=tmp->next;
                free(tmp);
                tmp=pre->next;
                manager->song_count--;
            }
        }
        else
        {
        pre=tmp;
        tmp=tmp->next;
        }
    }
    idupdate(manager);
    export_playlist(manager,"song_list_result.txt");
    if(sum==0)
    printf("不存在\n");
    return sum;
}

// 4. 播放歌曲
int play_song_by_title(PlaylistManager* manager, const char* title){
    if(manager->head==NULL)
    return 0;
    Song *tmp=manager->head;
    while(tmp!=NULL&&(strcmp(tmp->title,title))!=0)
    {
        tmp=tmp->next;
    }
    if(tmp!=NULL)
    {
        play_audio(tmp->filepath);
        manager->current=tmp;
        return 1;
    }
    else
    return 0;
    
}

// 5. 将播放列表保存到文件
int export_playlist(PlaylistManager* manager, const char* filename) {
    if(manager->song_count==0)
    {
        return 0;
    }
    FILE *fp=fopen(filename,"w");
    Song *tmp=manager->head;
    while(tmp!=NULL)
    {
        fprintf(fp,"%s,%s,%s\n",tmp->title,tmp->artist,tmp->filepath);
        tmp=tmp->next;
    }
    fclose(fp);
    return 1;
}

// 6. 随机播放歌曲（非必做）
int play_song_random(PlaylistManager* manager) {
    if (manager->song_count == 0) 
    {
        printf("播放列表为空，无法播放。\n");
        return 0;
    }
    int num=rand()%manager->song_count+1;
    int cnt=1;
    if(manager->song_count==0)
    return 0;
    Song *tmp=manager->head;
    while(cnt!=num)
    {
        tmp=tmp->next;
        cnt++;
    }
    play_audio(tmp->filepath);
    manager->current=tmp;
    return 1;
}

// 7. 在指定位置插入歌曲（非必做）
int insert_song_at(PlaylistManager* manager, int position, const char* title, 
                    const char* artist, const char* filepath) {
    if(position>=manager->song_count)
    {
        printf("插入位置非法");
        return 0;
    }
    Song *newsong=(Song*)malloc(sizeof(Song));
    manager->song_count++;
    newsong->next=NULL;
    strcpy(newsong->title,title);
    strcpy(newsong->artist,artist);
    strcpy(newsong->filepath,filepath);
    if(position==1)
    {
        newsong->next=manager->head;
        manager->head=newsong;
        if(manager->tail == NULL) 
        manager->tail = newsong;
        idupdate(manager);
        return 1;
    }
    Song *tmp=manager->head,*pre=NULL;
    while(tmp!=NULL&&tmp->id!=position)
    {
        pre=tmp;
        tmp=tmp->next;
    }
    pre->next=newsong;
    newsong->next=tmp;
    idupdate(manager);
    export_playlist(manager,"song_list_result.txt");
    return 1;

}

// 8. 销毁整个链表（非必做）
void destroy_playlist(PlaylistManager* manager) {
    Song* current = manager->head;
    while (current != NULL) {
        Song* next = current->next;
        free(current);
        current = next;
    }
    init_playlist_manager(manager);
    printf("播放列表已清空\n");
}


void display_menu() {
    printf("\n");
    printf("链表音乐播放器管理器\n");
    printf("==========================================\n");
    printf("1. 人工添加歌曲\n");
    printf("2. 显示播放列表\n");
    printf("3. 删除歌曲 (按标题)\n");
    printf("4. 播放歌曲 (按标题)\n");
    printf("5. 导出歌单\n");
    printf("6. 随机播放歌曲(非必做)\n");
    printf("7. 在指定位置添加歌曲(非必做)\n");
    printf("8. 清空播放列表(非必做)\n");
    printf("0. 退出程序\n");
    printf("==========================================\n");
    printf("请选择操作 (0-8): ");
}



// 清除输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 获取用户输入的字符串
void get_user_input(char* buffer, int size, const char* prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    // 去除换行符
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

// 主函数 - 交互式程序
int main() {
    srand(time(NULL));

    PlaylistManager manager;
    init_playlist_manager(&manager);
    load_songs_from_file(&manager,"song_list.txt");
    printf("=== 链表音乐播放器管理器 ===\n");
    printf("已加载 %d 首示例歌曲\n", manager.song_count);

    int choice;
    char input[100];

    do {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            printf("无效输入，请输入数字\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {               // 添加歌曲
                char title[100], artist[50], filepath[300];
                float duration;

                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                clear_input_buffer();

                add_song(&manager, title, artist, filepath);
                break;
            }
            case 2:{                // 显示播放列表 (正向)
                display_playlist(&manager);
                break;
            }
            case 3: {               // 删除歌曲 (按标题)
                char title[100];
                get_user_input(title, sizeof(title), "请输入要删除的歌曲标题: ");
                delete_songs_by_title(&manager, title);
                break;
            }
            case 4: {                 // 按歌曲名播放歌曲
                char title[100];
                get_user_input(title, sizeof(title), "请输入要播放的歌曲标题: ");
                int res = play_song_by_title(&manager, title);
                break;
            }
            case 5: {
                char path2export[300];
                get_user_input(path2export, sizeof(path2export), "请输入要导出的目标文件名: ");
                export_playlist(&manager, path2export);
                break;
            }
            case 6: {
                play_song_random(&manager);
                break;
            }
            case 7: {
                char title[100], artist[50], filepath[300];
                int position;
                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                printf("请输入歌曲插入位置: ");
                scanf("%d", &position);
                insert_song_at(&manager, position, title, artist, filepath);
                break;
            }
            case 8: {
                destroy_playlist(&manager);
                break;
            }
            case 0: // 退出程序
                printf("感谢使用链表音乐播放器管理器!\n");
                break;

            default:
                printf("无效选择，请重新输入\n");
                break;
        }

        // 暂停，让用户看到结果
        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
        }



    } while (choice != 0);

    // 清理内存
    destroy_playlist(&manager);

    return 0;
}

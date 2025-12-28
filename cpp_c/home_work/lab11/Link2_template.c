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
    struct Song* prev;
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
int delete_song_by_title(PlaylistManager* manager, const char* title);                   // 删除指定名字的音乐
int play_song_by_title(PlaylistManager* manager, const char* title);                     // 根据名字播放音乐
void display_playlist(PlaylistManager* manager);                                // 显示播放列表（正向）
void display_playlist_reverse(PlaylistManager* manager);                        // 显示播放列表（反向）
int export_playlist(PlaylistManager* manager, const char* filename);            // 导出歌单
void next_song(PlaylistManager* manager);                                       // 下一首歌
void previous_song(PlaylistManager* manager);                                   // 上一首歌
int play_song_random(PlaylistManager* manager);                                 // 随机播放音乐（非必做）
int insert_song_at(PlaylistManager* manager, int position, const char* title, const char* artist, const char* filepath);    // 向指定位置添加音乐（非必做）
void clear_playlist(PlaylistManager* manager);                                  // 清空播放列表（非必做）
void sort_by_title(PlaylistManager* manager);                                   // 按照歌曲名排序（非必做）


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
// void play_audio(const char* filename){
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Founded File!!");
//     }
//     snprintf(command, sizeof(command), "start \"\" \"%s\"", filename);
//     int ret = system(command);
//     if (ret != 0) {
//         printf("播放失败或中断，请检查文件格式是否支持。\n");
//     }
    
//     // 或者使用 Windows Media Player
//     // sprintf(command, "wmplayer \"%s\"", filename);
//     // system(command);
// }
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
void play_audio(const char* filename){
    printf("Playing %s ...", filename);
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
}
// 初始化播放管理器
void init_playlist_manager(PlaylistManager* manager){
    manager->head = NULL;
    manager->tail = NULL;
    manager->current = NULL;
    manager->song_count = 0;
}

// 从文件读取内容构建双向链表
int load_songs_from_file(PlaylistManager* manager, const char* filename) {
    FILE *fp=fopen(filename,"r");
    if (fp==NULL) {
        perror("Failed to open file");
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
            newsong->next=NULL;
            newsong->prev=NULL;
            continue;
        }
        newsong->prev=manager->tail;
        manager->tail->next=newsong;
        manager->tail=newsong;
    }
    fclose(fp);
    if(manager->song_count!=0)
    return manager->song_count;
    return 0;
}

// 1. 在链表末尾添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, const char* filepath) {
    Song *newsong=(Song*)malloc(sizeof(Song));
                manager->song_count++;
                newsong->id=manager->song_count;
                newsong->next=NULL;
                newsong->prev=NULL;
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
                    newsong->prev=manager->tail;
                    manager->tail->next=newsong;
                    manager->tail=newsong;
                }
                idupdate(manager);
                export_playlist(manager,"song_list_result.txt");
    return;
}

// 2. 按标题删除歌曲
int delete_song_by_title(PlaylistManager* manager, const char* title) {
    if (manager->head == NULL) return 0;

    Song *tmp = manager->head;
    int sum = 0;
    while (tmp != NULL) {
        if (strcmp(title, tmp->title) == 0) {
            Song *to_delete = tmp;
            sum++;
            manager->song_count--;

            if (manager->current == to_delete) manager->current = NULL;
            if (to_delete == manager->head) 
            {
                manager->head = to_delete->next;
                if (manager->head != NULL) 
                {
                    manager->head->prev = NULL;
                } else {
                    manager->tail = NULL;
                }
                tmp = manager->head;
            } else if (to_delete == manager->tail)
            {
                manager->tail = to_delete->prev;
                manager->tail->next = NULL;
                tmp = NULL; 
            } else 
            {
                to_delete->prev->next = to_delete->next;
                to_delete->next->prev = to_delete->prev;
                tmp = to_delete->next;
            }
            free(to_delete);
        } else {
            tmp = tmp->next;
        }
    }
    idupdate(manager);
    export_playlist(manager,"song_list_result.txt");
    return sum;
}

// 3. 播放歌曲
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
    return 0;
}

// 4. 显示播放列表（正向遍历）
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

// 5. 显示播放列表（反向遍历）
void display_playlist_reverse(PlaylistManager* manager) {
    if(manager->tail==NULL)
    return;
    Song *tmp=manager->tail;
    while(tmp!=NULL)
    {
        printf("%s %s %s\n",tmp->title,tmp->artist,tmp->filepath);
        tmp=tmp->prev;
    }
    return;
}

// 6. 将播放列表保存到文件
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

// 7. 下一首
void next_song(PlaylistManager* manager) {
    Song *curr=manager->current;
    if(curr==NULL)
    return;
    if(curr->next==NULL)
    {
        printf("已经是最后一首");
    }
    else{
        play_audio(curr->next->filepath);
        manager->current=manager->current->next;
    }
    return;
}

// 8. 上一首
void previous_song(PlaylistManager* manager) {
    Song *curr=manager->current;
    if(curr==NULL)
    return;
    if(curr->prev==NULL)
    {
        printf("已经是第一首");
    }
    else{
        play_audio(curr->prev->filepath);
        manager->current=manager->current->prev;
    }
    return;
}

// 9. 随机播放歌曲（非必做）
int play_song_random(PlaylistManager* manager) {
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

// 10. 在指定位置插入歌曲（非必做）
int insert_song_at(PlaylistManager* manager, int position, const char* title, 
                    const char* artist, const char* filepath) {
    if (position < 1 || position > manager->song_count + 1) return 0;

    Song *newsong = (Song*)malloc(sizeof(Song));
    strcpy(newsong->title, title);
    strcpy(newsong->artist, artist);
    strcpy(newsong->filepath, filepath);

    if (position == 1) { 
        newsong->prev = NULL;
        newsong->next = manager->head;
        if (manager->head) manager->head->prev = newsong;
        manager->head = newsong;
        if (manager->tail == NULL) manager->tail = newsong;
    } else if (position == manager->song_count + 1) { 
        newsong->next = NULL;
        newsong->prev = manager->tail;
        if (manager->tail) manager->tail->next = newsong;
        manager->tail = newsong;
    } else { 
        Song *tmp = manager->head;
        for (int i = 1; i < position; i++) tmp = tmp->next; 
        
        newsong->next = tmp;
        newsong->prev = tmp->prev;
        if (tmp->prev) tmp->prev->next = newsong;
        tmp->prev = newsong;
    }
    
    manager->song_count++;
    idupdate(manager);
    export_playlist(manager,"song_list_result.txt");
    return 1;
}

// 12. 按歌曲标题排序（非必做）
void sort_by_title(PlaylistManager* manager) {
    return;
}

// 销毁整个链表
void clear_playlist(PlaylistManager* manager) {
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
    printf("1. 添加歌曲\n");
    printf("2. 删除歌曲 (按标题)\n");
    printf("3. 播放歌曲 (按标题)\n");
    printf("4. 显示播放列表 (正向)\n");
    printf("5. 显示播放列表 (逆向)\n");
    printf("6. 导出歌单\n");
    printf("7. 切换到下一首歌\n");
    printf("8. 切换到上一首歌\n");
    printf("9. 随机播放歌曲(非必做)\n");
    printf("10. 在指定位置添加歌曲(非必做)\n");
    printf("11. 清空播放列表(非必做)\n");
    printf("12. 按照歌曲名排序(非必做)\n");
    printf("0. 退出程序\n");
    printf("==========================================\n");
    printf("请选择操作 (0-12): ");
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

    printf("=== 双向链表音乐播放器管理器 ===\n");
    printf("已加载 %d 首示例歌曲\n", manager.song_count);
    manager.current = manager.head;
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
            case 1: {                   // 添加歌曲
                char title[100], artist[50], filepath[300];
                float duration;

                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                clear_input_buffer();

                add_song(&manager, title, artist, filepath);
                break;
            }
            case 2: {                   // 删除歌曲 (按标题)
                char title[100];
                get_user_input(title, sizeof(title), "请输入要删除的歌曲标题: ");
                int res = delete_song_by_title(&manager, title);
                break;
            }
            case 3: {                   // 播放歌曲（按歌曲名）
                char title[100];
                get_user_input(title, sizeof(title), "请输入要播放的歌曲标题: ");
                int res = play_song_by_title(&manager, title);
                break;
            }
            case 4: {                   // 显示播放列表（正向）
                display_playlist(&manager);
                break;
            }
            case 5: {                   // 显示播放列表（逆向）
                display_playlist_reverse(&manager);
                break;
            }
            case 6: {                   // 导出播放列表
                char path2export[300];
                get_user_input(path2export, sizeof(path2export), "请输入要导出的目标文件名: ");
                int res = export_playlist(&manager, path2export);
                break;
            }
            case 7: {                   // 播放下一首歌曲
                next_song(&manager);
                break;
            }
            case 8: {                   // 播放上一首歌曲
                previous_song(&manager);
                break;
            }
            case 9: {                   // 随机播放歌曲(非必做)
                int res = play_song_random(&manager);
                break;
            }
            case 10: {                  // 在指定位置添加歌曲(非必做)
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
            case 11: {                  // 清空播放列表(非必做)
                clear_playlist(&manager);
                break;
            }
            case 12: {                  // 按照歌曲名排序(非必做)
                sort_by_title(&manager);
                break;
            }
            case 0: // 退出程序
                printf("感谢使用链表音乐播放器管理器!\n");
                break;
            default:
                printf("? 无效选择，请重新输入\n");
                break;
        }

        // 暂停，让用户看到结果
        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
        }

    } while (choice != 0);

    // 清理内存
    clear_playlist(&manager);

    return 0;
}
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "project.h"
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(Project& project, QWidget *parent = 0);
    ~MainWindow();


signals:
    // TOOL SIGNALS
    // Intended Reciever: Tool Class
    void pencil_tool_selected();
    void brush_tool_selected();
    void line_tool_selected();
    void eraser_tool_selected();

    // BRUSH SIGNALS
    // Intended Reciever: Tool Class
    void brush_size_changed(int d);
    void brush_color_changed(QColor c);

    // FRAME SIGNALS
    // Intended Reciever: Project Class
    void next_frame_requested();
    void previous_frame_requested();
    void new_frame_requested();

    // HISTORY MENU
    // Intended Reciever: Project Class
    // unsure if Hash is the type we will be using to identify history frames, open to changing this.
    void history_reversion_requested();

    // PREVIEW MENU
    // Intended Reciever: (???)
    void preview_fps_changed(int fps);
    void zoom_in_requested();
    void zoom_out_requested();

    // CANVAS
    // Intended Reciever: Tool Class
    void mouse_down_pos(int x, int y);      // fires when the mouse pos changes while the mouse button is held
    void mouse_down(int x, int y);          // mouse has been clicked down
    void mouse_up(int x, int y);            // mouse has been released
    void mouse_left();                      // indicates the mouse has left the canvas

public slots:

    // FROM PROJECT
    void update_canvas(QImage * i);
    void update_preview(QImage * i);
    void update_current_frame_label(int current_frame, int total_frames);
    void add_history_menu_entry(std::string name, std::string hash);

    // FROM CANVAS
    void c_mouse_down_pos();
    void c_mouse_down();
    void c_mouse_up();
    void c_mouse_left();

private slots:
    // QT GENERATED SLOTS FOR UI ACTIONS
    void on_PencilToolButton_clicked();
    void on_BrushToolButton_clicked();
    void on_LineToolButton_clicked();
    void on_EraserToolButton_clicked();
    void on_DiameterSpinBox_editingFinished();
    void on_ColorSelectButton_clicked();
    void on_PreviousFrameButton_clicked();
    void on_pushButton_2_clicked();
    void on_AddFrameButton_clicked();
    void on_LoadHistoryButton_clicked();
    void on_PreviewSpeedSpinBox_editingFinished();
    void on_ZoomInButton_clicked();
    void on_ZoomOutButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

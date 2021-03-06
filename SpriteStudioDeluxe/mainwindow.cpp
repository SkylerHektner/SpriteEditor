#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.h"
#include <QColorDialog>
#include <QPixmap>
#include <QListWidgetItem>
#include <QFileDialog>
#include <string>
#include <iostream>


MainWindow::MainWindow(Project& project, Tools& tools, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // STARTING CONDITIONS
    ui->setupUi(this);
    ui->canvas->setAlignment(Qt::AlignTop);
    ui->canvas->setAlignment(Qt::AlignLeft);
    ui->CurrentColorLabel->setStyleSheet("QLabel { background-color : black; color : black; }");
    project.update_canvas();
    project.update_frame_label(1,1);


    // QIMAGE UPDATE CONNECTIONS
    connect(&tools, SIGNAL(update_can(QImage*)), this, SLOT(update_canvas(QImage*)));
    connect(&project, SIGNAL(send_update(QImage*)), this, SLOT(update_canvas(QImage*)));
    connect(project.preview, SIGNAL(thread_end(QImage*)), this, SLOT(update_preview(QImage*)));

    //MOUSE ACTION CONNECTIONS
    connect(ui->canvas, SIGNAL(c_mouse_down()), this, SLOT(c_mouse_down()));
    connect(ui->canvas, SIGNAL(c_mouse_up()), this, SLOT(c_mouse_up()));
    connect(ui->canvas, SIGNAL(c_mouse_down_pos(int, int)), this, SLOT(c_mouse_down_pos()));
    connect(ui->canvas, SIGNAL(c_mouse_left()), this, SLOT(c_mouse_left()));
    connect(this, SIGNAL(mouse_drag(int, int)), &tools, SLOT(on_mouse_drag(int,int)));
    connect(this, SIGNAL(mouse_down(int, int)), &tools, SLOT(on_mouse_down(int,int)));
    connect(this, SIGNAL(mouse_up(int, int)), &tools, SLOT(on_mouse_up(int,int)));

    //FRAME CONNECTIONS
    connect(this, SIGNAL(new_frame_requested()), &project, SLOT(add_frame()));
    connect(this, SIGNAL(next_frame_requested()), &project, SLOT(next_frame()));
    connect(this, SIGNAL(previous_frame_requested()), &project, SLOT(previous_frame()));
    connect(&project, SIGNAL(frame_changed(Frame*)), &tools, SLOT(frame_changed(Frame*)));
    connect(&project, SIGNAL(update_frame_label(int,int)), this, SLOT(update_current_frame_label(int,int)));
    connect(this, SIGNAL(rotate_frame()), &project, SLOT(rotate_frame()));
    connect(&project, SIGNAL(show_window()), this, SLOT(show_window()));
    connect(&project, SIGNAL(hide_window()), this, SLOT(hide_window()));

    // TOOL CHANGE CONNECTIONS
    connect(this, SIGNAL(tool_changed(int)), &tools, SLOT(tool_selected(int)));
    connect(this, SIGNAL(brush_size_changed(int)), &tools, SLOT(brush_size_changed(int)));
    connect(this, SIGNAL(brush_color_changed(QColor)), &tools, SLOT(change_color(QColor)));
    connect(this, SIGNAL(clear_canvas()), &tools, SLOT(clear_canvas()));
    connect(this, SIGNAL(fill_canvas()), &tools, SLOT(fill_canvas()));
    connect (this, SIGNAL(history_reversion_requested()), &project, SLOT(history_step_back()));
    connect(this, SIGNAL(zoom_in_requested()), &project, SLOT(zoom_in()));
    connect(this, SIGNAL(zoom_out_requested()), &project, SLOT(zoom_out()));

    // IO CONNECTIONS
    connect(this, SIGNAL(save_sprite(QString)), &project, SLOT(save_project(QString)));
    connect(this, SIGNAL(load_sprite(QString)), &project, SLOT(load_project(QString)));
    connect(this, SIGNAL(new_sprite()), &project, SLOT(new_project()));
    connect(this, SIGNAL(export_sprite(QString)), &project, SLOT(export_project(QString)));

    // UI IMAGE INITIALIZATION

    float icon_scale = .5;
    QPixmap pencil("./resources/icons/pencil.png");
    QPixmap eraser("./resources/icons/eraser.png");
    QPixmap line("./resources/icons/line.png");
    QPixmap brush("./resources/icons/brush.png");
    QPixmap rectangle("./resources/icons/rectangle.png");
    QPixmap rectangle_filled("./resources/icons/rectangle_filled.png");
    QPixmap clear("./resources/icons/clear.png");
    QPixmap mirror_x("./resources/icons/mirror_x.png");
    QPixmap mirror_y("./resources/icons/mirror_y.png");
    QPixmap fill("./resources/icons/fill.png");

    QIcon i_pencil(pencil);
    QIcon i_eraser(eraser);
    QIcon i_line(line);
    QIcon i_brush(brush);
    QIcon i_rectangle(rectangle);
    QIcon i_rectangle_filled(rectangle_filled);
    QIcon i_clear(clear);
    QIcon i_mirror_x(mirror_x);
    QIcon i_mirror_y(mirror_y);
    QIcon i_fill(fill);

    ui->PencilToolButton->setIcon(i_pencil);
    ui->EraserToolButton->setIcon(i_eraser);
    ui->LineToolButton->setIcon(i_line);
    ui->BrushToolButton->setIcon(i_brush);
    ui->RectangleToolButton->setIcon(i_rectangle);
    ui->FilledRectangleButton->setIcon(i_rectangle_filled);
    ui->ClearCanvasButton->setIcon(i_clear);
    ui->MirrorXToolButton->setIcon(i_mirror_x);
    ui->MirrorYToolButton->setIcon(i_mirror_y);
    ui->FillAllButton->setIcon(i_fill);

    ui->PencilToolButton->setIconSize(pencil.rect().size()*icon_scale);
    ui->EraserToolButton->setIconSize(eraser.rect().size()*icon_scale);
    ui->LineToolButton->setIconSize(line.rect().size()*icon_scale);
    ui->BrushToolButton->setIconSize(brush.rect().size()*icon_scale);
    ui->RectangleToolButton->setIconSize(rectangle.rect().size()*icon_scale);
    ui->FilledRectangleButton->setIconSize(rectangle_filled.rect().size()*icon_scale);
    ui->ClearCanvasButton->setIconSize(clear.rect().size()*icon_scale);
    ui->MirrorXToolButton->setIconSize(mirror_x.rect().size()*icon_scale);
    ui->MirrorYToolButton->setIconSize(mirror_y.rect().size()*icon_scale);
    ui->FillAllButton->setIconSize(fill.rect().size()*icon_scale);

}

MainWindow::~MainWindow(){
    delete ui;
}


// PROJECT SIGNAL HANDLERS

void MainWindow::update_canvas(QImage *i)
{
    ui->canvas->setPixmap(QPixmap::fromImage(*i));
    ui->canvas->setMaximumSize(i->size() * 1/i->devicePixelRatio());
    ui->canvas->setMinimumSize(i->size() * 1/i->devicePixelRatio());
    ui->canvas->show();
}

void MainWindow::update_preview(QImage *i)
{
    ui->PreviewLabel->setPixmap(QPixmap::fromImage(*i));
    ui->PreviewLabel->setScaledContents(true);
    ui->PreviewLabel->show();
}

void MainWindow::update_current_frame_label(int current_frame, int total_frames)
{
    QString s(("Current Frame: " + std::to_string(current_frame) + "/" + std::to_string(total_frames)).c_str());
    ui->CurrentFrameLabel->setText(s);
}


// CANVAS SIGNAL HANDLERS

void MainWindow::c_mouse_down_pos()
{
    int x = ui->canvas->x;
    int y = ui->canvas->y;
    emit mouse_drag(x, y);
}

void MainWindow::c_mouse_down()
{
    int x = ui->canvas->x;
    int y = ui->canvas->y;
    emit mouse_down(x, y);
}

void MainWindow::c_mouse_up()
{
    int x = ui->canvas->x;
    int y = ui->canvas->y;
    emit mouse_up(x, y);
}

void MainWindow::c_mouse_left()
{
    emit mouse_left();
}


// QT AUTO IMPLEMENTED SIGNAL HANDLERS

void MainWindow::on_PencilToolButton_clicked()
{
    emit tool_changed(1);
}

void MainWindow::on_BrushToolButton_clicked()
{
    emit tool_changed(2);
}

void MainWindow::on_LineToolButton_clicked()
{
    emit tool_changed(3);
}

void MainWindow::on_EraserToolButton_clicked()
{
    emit tool_changed(4);
}

void MainWindow::on_MirrorXToolButton_clicked()
{
    emit tool_changed(5);
}
void MainWindow::on_MirrorYToolButton_clicked()
{
    emit tool_changed(6);
}

void MainWindow::on_DiameterSpinBox_editingFinished()
{
    int x = ui->DiameterSpinBox->value();
    emit brush_size_changed(x);
}

void MainWindow::on_ColorSelectButton_clicked()
{
    // Get the color from a color dialog
    QColor color = QColorDialog::getColor(Qt::white, this);

    // assign the current color label that selected color
    QImage new_color_swatch(40, 40, QImage::Format_ARGB32);
    new_color_swatch.fill(color);
    ui->CurrentColorLabel->setPixmap(QPixmap::fromImage(new_color_swatch));
    ui->CurrentColorLabel->show();

    // emit Brush color change event so the model knows
    emit brush_color_changed(color);
}

void MainWindow::on_PreviousFrameButton_clicked()
{
    emit previous_frame_requested();
}

void MainWindow::on_pushButton_2_clicked()
{
    emit next_frame_requested();
}

void MainWindow::on_AddFrameButton_clicked()
{
    emit new_frame_requested();
}

void MainWindow::on_ZoomInButton_clicked()
{
    emit zoom_in_requested();
}

void MainWindow::on_ZoomOutButton_clicked()
{
    emit zoom_out_requested();
}

void MainWindow::on_StepBackButton_clicked()
{
    emit history_reversion_requested();
}

void MainWindow::on_RectangleToolButton_clicked()
{
    emit tool_changed(7);
}

void MainWindow::on_FilledRectangleButton_clicked()
{
    emit tool_changed(8);
}

void MainWindow::on_ClearCanvasButton_clicked()
{
    emit clear_canvas();
}

void MainWindow::on_FillAllButton_clicked()
{
    emit fill_canvas();
}

void MainWindow::on_actionOpen_triggered()
{
    project_filename = QFileDialog::getOpenFileName(this, tr("Open Sprite"), " ", tr("Sprite (*.ssp);;All Files (*)"));
    if (project_filename != NULL)
    {
        emit load_sprite(project_filename);
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    project_filename = QFileDialog::getSaveFileName(this, tr("Save Sprite"), " ", tr("Sprite (*.ssp);;All Files (*)"));
    emit save_sprite(project_filename);
}

void MainWindow::on_actionRotate_90_triggered()
{
    emit rotate_frame();
}

void MainWindow::on_actionNew_triggered()
{
    emit new_sprite();
}

void MainWindow::show_window()
{
    this->show();
}

void MainWindow::hide_window()
{
    this->hide();
}

void MainWindow::on_actionSave_triggered()
{
    if(project_filename.isEmpty())
    {
        project_filename = QFileDialog::getSaveFileName(this, tr("Save Sprite"), " ", tr("Sprite (*.ssp);;All Files (*)"));
    }
    emit save_sprite(project_filename);
}

void MainWindow::on_actionExport_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Export Sprite"), " ", tr("GIF (*.gif);;PNG (*.png)"));
    emit export_sprite(filename);
}

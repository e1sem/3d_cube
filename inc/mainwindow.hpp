#ifndef CUBE3D_MAINWINDOW_HPP_
#define CUBE3D_MAINWINDOW_HPP_

/******************************************************************************/

#include <QWidget>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

#include <memory>

/******************************************************************************/

class SceneModifier;
class InputDialog;
class VirtualPort;
class ModelLoader;

/******************************************************************************/

class MainWindow
    :   public QWidget
{

/******************************************************************************/

    Q_OBJECT

/******************************************************************************/

public:

/******************************************************************************/

    explicit MainWindow( QWidget* _parent = nullptr );

    ~MainWindow();

/******************************************************************************/

private slots:

/******************************************************************************/

    void initWidget();

    void init3DView();

    void initWindowContainer();

    void initCamController();

/******************************************************************************/

    void initSceneModifier();

    void initInputDialog();

    void initVirtualPort();

    void initModelLoader();

/******************************************************************************/

private:

/******************************************************************************/

    QWidget* m_pWindowContainer;

    Qt3DCore::QEntity* m_pRootEntity;

    Qt3DExtras::Qt3DWindow* m_p3dView;

    Qt3DExtras::QFirstPersonCameraController* m_pCamController;

/******************************************************************************/

    SceneModifier* m_pSceneModifier;

    InputDialog* m_pInputDialog;

    VirtualPort* m_pVirtualPort;

    ModelLoader* m_modelLoader;

/******************************************************************************/

}; // class MainWindow

/******************************************************************************/

#endif // CUBE3D_MAINWINDOW_HPP_

#include <QtWidgets/QHBoxLayout>
#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DCore/qtransform.h>

#include "scenemodifier.hpp"
#include "mainwindow.hpp"
#include "inputdialog.hpp"
#include "modelloader.hpp"
#include "serialport.hpp"
#include "parameters.hpp"

/******************************************************************************/

MainWindow::MainWindow( QWidget* _parent )
    :   QWidget( _parent )
{
    initWidget();
    init3DView();
    initWindowContainer();
    initCamController();
    initSceneModifier();
    initVirtualPort();
    initInputDialog();
    initModelLoader();
}

/******************************************************************************/

MainWindow::~MainWindow()
{
    delete m_pInputDialog;
    delete m_pVirtualPort;
    delete m_pWindowContainer;
}

/******************************************************************************/

void
MainWindow::initWidget()
{
    // Root entity
    m_pRootEntity = new Qt3DCore::QEntity();

    setWindowTitle( ProjOpt::windowTitle );
    setFixedWidth( ProjOpt::windowWidth );
    setFixedHeight( ProjOpt::windowHeight );
}

/******************************************************************************/

void
MainWindow::init3DView()
{
    m_p3dView = new Qt3DExtras::Qt3DWindow();
    m_p3dView->setRootEntity( m_pRootEntity );

    auto frameGraph = m_p3dView->defaultFrameGraph();
    frameGraph->setClearColor( ProjOpt::sceneAppearanceColor );

    Qt3DInput::QInputAspect* input = new Qt3DInput::QInputAspect();
    m_p3dView->registerAspect( input );
}

/******************************************************************************/

void
MainWindow::initWindowContainer()
{
    m_pWindowContainer = QWidget::createWindowContainer( m_p3dView );

    QHBoxLayout *hLayout = new QHBoxLayout( this );
    QVBoxLayout *vLayout = new QVBoxLayout();

    vLayout->setAlignment( Qt::AlignTop );
    hLayout->addWidget( m_pWindowContainer, 1 );
    hLayout->addLayout( vLayout );
}

/******************************************************************************/

void
MainWindow::initCamController()
{
    // Camera entity
    Qt3DRender::QCamera *cameraEntity = m_p3dView->camera();
    cameraEntity->lens()->setPerspectiveProjection(
                45.0f
            ,   16.0f/9.0f
            ,   0.1f
            ,   1000.0f
        );
    cameraEntity->setPosition( QVector3D( 10, 10, 10 ) );
    cameraEntity->setUpVector( QVector3D( 0, 1, 0) ) ;
    cameraEntity->setViewCenter( QVector3D( 0, 0, 0 ) );

    // Light
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity( m_pRootEntity );
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight( lightEntity );

    light->setColor( "white" );
    light->setIntensity( 1 );

    lightEntity->addComponent( light );

    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform( lightEntity );

    lightTransform->setTranslation( cameraEntity->position() );
    lightEntity->addComponent( lightTransform );

    // For camera controls
    m_pCamController = new Qt3DExtras::QFirstPersonCameraController( m_pRootEntity );

    m_pCamController->setCamera( cameraEntity );
}

/******************************************************************************/

void
MainWindow::initSceneModifier()
{
    m_pSceneModifier = new SceneModifier( m_pRootEntity );
    m_pSceneModifier->enableCuboid( true );

}

/******************************************************************************/

void
MainWindow::initInputDialog()
{
    m_pInputDialog = new InputDialog( this );

    m_pInputDialog->setSerialPort( m_pVirtualPort );
    m_pInputDialog->show();
}

/******************************************************************************/

void
MainWindow::initVirtualPort()
{
    m_pVirtualPort = new VirtualPort;

    m_pVirtualPort->setModifier( m_pSceneModifier );
}

/******************************************************************************/

void
MainWindow::initModelLoader()
{
    m_modelLoader = new ModelLoader( this );
    m_modelLoader->setSceneModifier( m_pSceneModifier );
    m_pSceneModifier->setModelLoader( m_modelLoader );
}

/******************************************************************************/

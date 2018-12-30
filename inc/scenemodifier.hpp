#ifndef __SCENEMODIFIER_HPP__
#define __SCENEMODIFIER_HPP__

/******************************************************************************/

#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DRender/QMesh>

/******************************************************************************/

class ModelLoader;

/******************************************************************************/

class SceneModifier
    :   public QObject
{

/******************************************************************************/

    Q_OBJECT

/******************************************************************************/

public:

/******************************************************************************/

    explicit SceneModifier( Qt3DCore::QEntity* rootEntity );

    ~SceneModifier();

/******************************************************************************/

    void setModelLoader( ModelLoader* _modelLoader );

/******************************************************************************/

    void enableCuboid( bool enabled ) noexcept;

    void setCuboidRotationX( float _angle ) noexcept;

    void setCuboidRotationY( float _angle ) noexcept;

    float getCuboidRotationX() noexcept;

    float getCuboidRotationY() noexcept;

/******************************************************************************/

public slots:

    void onModelPathChanged();

private:

/******************************************************************************/

    Q_DISABLE_COPY(SceneModifier)

/******************************************************************************/

    Qt3DCore::QEntity* m_modelEntity;

    Qt3DCore::QTransform* m_transformData;

    Qt3DRender::QMesh* m_objModel;

    ModelLoader* m_pModelLoader;

/******************************************************************************/

}; // class SceneModifier

/******************************************************************************/

#endif // __SCENEMODIFIER_HPP__

#ifndef DUISCENEMANAGER_STUB
#define DUISCENEMANAGER_STUB

#include "duiscenemanager.h"
#include <stubbase.h>


// 1. DECLARE STUB
// FIXME - stubgen is not yet finished
class DuiSceneManagerStub : public StubBase {
  public:
  virtual void DuiSceneManagerConstructor(DuiScene *scene, QObject *parent);
  virtual void DuiSceneManagerDestructor();
  virtual DuiScene * scene();
  virtual Dui::Orientation orientation() const;
  virtual Dui::OrientationAngle orientationAngle() const;
  virtual QSize visibleSceneSize(Dui::Orientation orientation) const;
  virtual QSize visibleSceneSize() const;
  virtual void setOrientationAngle(Dui::OrientationAngle angle, Dui::OrientationChangeMode mode);
  virtual void requestSoftwareInputPanel(QGraphicsWidget *inputWidget);
  virtual void closeSoftwareInputPanel();
  virtual void showWindow(DuiSceneWindow *window, DuiSceneWindow::DeletionPolicy policy);
  virtual void showWindowNow(DuiSceneWindow *window, DuiSceneWindow::DeletionPolicy policy);
  virtual int execDialog(DuiDialog *dialog);
  virtual void hideWindow(DuiSceneWindow *window);
  virtual void hideWindowNow(DuiSceneWindow *window);
  virtual void closeWindow(DuiSceneWindow *window);
  virtual void closeWindowNow(DuiSceneWindow *window);
  virtual void orientationAboutToChange(const Dui::Orientation &orientation);
  virtual void orientationChanged(const Dui::Orientation &orientation);
  virtual void orientationChangeFinished(const Dui::Orientation &orientation);
  virtual bool eventFilter(QObject *watched, QEvent *event);
}; 

// 2. IMPLEMENT STUB
void DuiSceneManagerStub::DuiSceneManagerConstructor(DuiScene *scene, QObject *parent) {
  Q_UNUSED(scene);
  Q_UNUSED(parent);

}
void DuiSceneManagerStub::DuiSceneManagerDestructor() {

}
DuiScene * DuiSceneManagerStub::scene() {
  stubMethodEntered("scene");
  return stubReturnValue<DuiScene *>("scene");
}

Dui::Orientation DuiSceneManagerStub::orientation() const {
  stubMethodEntered("orientation");
  return stubReturnValue<Dui::Orientation>("orientation");
}

Dui::OrientationAngle DuiSceneManagerStub::orientationAngle() const {
  stubMethodEntered("orientationAngle");
  return stubReturnValue<Dui::OrientationAngle>("orientationAngle");
}

QSize DuiSceneManagerStub::visibleSceneSize(Dui::Orientation orientation) const {
  QList<ParameterBase*> params;
  params.append( new Parameter<Dui::Orientation >(orientation));
  stubMethodEntered("visibleSceneSize",params);
  return stubReturnValue<QSize>("visibleSceneSize");
}

QSize DuiSceneManagerStub::visibleSceneSize() const {
  stubMethodEntered("visibleSceneSize");
  return stubReturnValue<QSize>("visibleSceneSize");
}

void DuiSceneManagerStub::setOrientationAngle(Dui::OrientationAngle angle, Dui::OrientationChangeMode mode) {
  QList<ParameterBase*> params;
  params.append( new Parameter<Dui::OrientationAngle >(angle));
  params.append( new Parameter<Dui::OrientationChangeMode >(mode));
  stubMethodEntered("setOrientationAngle",params);
}

void DuiSceneManagerStub::requestSoftwareInputPanel(QGraphicsWidget *inputWidget) {
  QList<ParameterBase*> params;
  params.append( new Parameter<QGraphicsWidget * >(inputWidget));
  stubMethodEntered("requestSoftwareInputPanel",params);
}

void DuiSceneManagerStub::closeSoftwareInputPanel() {
  stubMethodEntered("closeSoftwareInputPanel");
}

void DuiSceneManagerStub::showWindow(DuiSceneWindow *window, DuiSceneWindow::DeletionPolicy policy) {
  QList<ParameterBase*> params;
  params.append( new Parameter<DuiSceneWindow * >(window));
  params.append( new Parameter<DuiSceneWindow::DeletionPolicy >(policy));
  stubMethodEntered("showWindow",params);
}

void DuiSceneManagerStub::showWindowNow(DuiSceneWindow *window, DuiSceneWindow::DeletionPolicy policy) {
  QList<ParameterBase*> params;
  params.append( new Parameter<DuiSceneWindow * >(window));
  params.append( new Parameter<DuiSceneWindow::DeletionPolicy >(policy));
  stubMethodEntered("showWindowNow",params);
}

int DuiSceneManagerStub::execDialog(DuiDialog *dialog) {
  QList<ParameterBase*> params;
  params.append( new Parameter<DuiDialog * >(dialog));
  stubMethodEntered("execDialog",params);
  return stubReturnValue<int>("execDialog");
}

void DuiSceneManagerStub::hideWindow(DuiSceneWindow *window) {
  QList<ParameterBase*> params;
  params.append( new Parameter<DuiSceneWindow * >(window));
  stubMethodEntered("hideWindow",params);
}

void DuiSceneManagerStub::hideWindowNow(DuiSceneWindow *window) {
  QList<ParameterBase*> params;
  params.append( new Parameter<DuiSceneWindow * >(window));
  stubMethodEntered("hideWindowNow",params);
}

void DuiSceneManagerStub::closeWindow(DuiSceneWindow *window) {
  QList<ParameterBase*> params;
  params.append( new Parameter<DuiSceneWindow * >(window));
  stubMethodEntered("closeWindow",params);
}

void DuiSceneManagerStub::closeWindowNow(DuiSceneWindow *window) {
  QList<ParameterBase*> params;
  params.append( new Parameter<DuiSceneWindow * >(window));
  stubMethodEntered("closeWindowNow",params);
}

void DuiSceneManagerStub::orientationAboutToChange(const Dui::Orientation &orientation) {
  QList<ParameterBase*> params;
  params.append( new Parameter<const Dui::Orientation & >(orientation));
  stubMethodEntered("orientationAboutToChange",params);
}

void DuiSceneManagerStub::orientationChanged(const Dui::Orientation &orientation) {
  QList<ParameterBase*> params;
  params.append( new Parameter<const Dui::Orientation & >(orientation));
  stubMethodEntered("orientationChanged",params);
}

void DuiSceneManagerStub::orientationChangeFinished(const Dui::Orientation &orientation) {
  QList<ParameterBase*> params;
  params.append( new Parameter<const Dui::Orientation & >(orientation));
  stubMethodEntered("orientationChangeFinished",params);
}

bool DuiSceneManagerStub::eventFilter(QObject *watched, QEvent *event) {
  QList<ParameterBase*> params;
  params.append( new Parameter<QObject * >(watched));
  params.append( new Parameter<QEvent * >(event));
  stubMethodEntered("eventFilter",params);
  return stubReturnValue<bool>("eventFilter");
}



// 3. CREATE A STUB INSTANCE
DuiSceneManagerStub gDefaultDuiSceneManagerStub;
DuiSceneManagerStub* gDuiSceneManagerStub = &gDefaultDuiSceneManagerStub;


// 4. CREATE A PROXY WHICH CALLS THE STUB
DuiSceneManager::DuiSceneManager(DuiScene *scene, QObject *parent) : d_ptr(NULL) {
  gDuiSceneManagerStub->DuiSceneManagerConstructor(scene, parent);
}

DuiSceneManager::~DuiSceneManager() {
  gDuiSceneManagerStub->DuiSceneManagerDestructor();
}

DuiScene * DuiSceneManager::scene() {
  return gDuiSceneManagerStub->scene();
}

Dui::Orientation DuiSceneManager::orientation() const {
  return gDuiSceneManagerStub->orientation();
}

Dui::OrientationAngle DuiSceneManager::orientationAngle() const {
  return gDuiSceneManagerStub->orientationAngle();
}

QSize DuiSceneManager::visibleSceneSize(Dui::Orientation orientation) const {
  return gDuiSceneManagerStub->visibleSceneSize(orientation);
}

QSize DuiSceneManager::visibleSceneSize() const {
  return gDuiSceneManagerStub->visibleSceneSize();
}

void DuiSceneManager::setOrientationAngle(Dui::OrientationAngle angle, Dui::OrientationChangeMode mode) {
  gDuiSceneManagerStub->setOrientationAngle(angle, mode);
}

void DuiSceneManager::requestSoftwareInputPanel(QGraphicsWidget *inputWidget) {
  gDuiSceneManagerStub->requestSoftwareInputPanel(inputWidget);
}

void DuiSceneManager::closeSoftwareInputPanel() {
  gDuiSceneManagerStub->closeSoftwareInputPanel();
}

void DuiSceneManager::showWindow(DuiSceneWindow *window, DuiSceneWindow::DeletionPolicy policy) {
  gDuiSceneManagerStub->showWindow(window, policy);
}

void DuiSceneManager::showWindowNow(DuiSceneWindow *window, DuiSceneWindow::DeletionPolicy policy) {
  gDuiSceneManagerStub->showWindowNow(window, policy);
}

int DuiSceneManager::execDialog(DuiDialog *dialog) {
  return gDuiSceneManagerStub->execDialog(dialog);
}

void DuiSceneManager::hideWindow(DuiSceneWindow *window) {
  gDuiSceneManagerStub->hideWindow(window);
}

void DuiSceneManager::hideWindowNow(DuiSceneWindow *window) {
  gDuiSceneManagerStub->hideWindowNow(window);
}

void DuiSceneManager::closeWindow(DuiSceneWindow *window) {
  gDuiSceneManagerStub->closeWindow(window);
}

void DuiSceneManager::closeWindowNow(DuiSceneWindow *window) {
  gDuiSceneManagerStub->closeWindowNow(window);
}

void DuiSceneManager::orientationAboutToChange(const Dui::Orientation &orientation) {
  gDuiSceneManagerStub->orientationAboutToChange(orientation);
}

void DuiSceneManager::orientationChanged(const Dui::Orientation &orientation) {
  gDuiSceneManagerStub->orientationChanged(orientation);
}

void DuiSceneManager::orientationChangeFinished(const Dui::Orientation &orientation) {
  gDuiSceneManagerStub->orientationChangeFinished(orientation);
}

bool DuiSceneManager::eventFilter(QObject *watched, QEvent *event) {
  return gDuiSceneManagerStub->eventFilter(watched, event);
}


#endif

#include "SMDialog.hpp"

SMDialog::SMDialog(QWidget* parent)
    : QDialog(parent)
{
    // Remove the '?' button
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

#ifndef INCLUDES_MODEL_IMODEL_HPP_
#define INCLUDES_MODEL_IMODEL_HPP_

#include <QtPlugin>

namespace ns_model {

class IModel {
 public:
  virtual ~IModel() {}

  virtual QString CalculateNotation(QString const &str) = 0;
};

}  // namespace ns_model

Q_DECLARE_INTERFACE(ns_model::IModel, "ns_model.IModel");

#endif  // INCLUDES_MODEL_IMODEL_HPP_

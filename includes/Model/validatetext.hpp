#ifndef INCLUDES_MODEL_VALIDATETEXT_HPP_
#define INCLUDES_MODEL_VALIDATETEXT_HPP_

#include <QString>

namespace ns_model {

class ValidateText {
 public:
  explicit ValidateText(QString const &str = "");
  ValidateText(ValidateText const &other) = default;
  ValidateText &operator=(ValidateText const &other) = default;

  void AddTextToStr(QString const &str);
  void SetBrackets(QString const &str, bool const is_smart, bool is_checked);

  bool IsLeftBracket(QString const &str);
  void set_text(QString const &str);
  QString get_text() const;
  bool IsValid() const;
  void ResetText();
  QString FixedForDisplayRepeat(QString str);
  QString ReplaceDummyFunctions(QString str);
  bool IsSign(QChar const &ch_);

  virtual ~ValidateText();

 private:
  QString text_;
  bool is_valid_;
  bool is_clear_;
};

}  // namespace ns_model

#endif  // INCLUDES_MODEL_VALIDATETEXT_HPP_

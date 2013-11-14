/* 
 * File:   ISqlResult.hpp
 * Author: xaqq
 *
 * Created on November 14, 2013, 8:09 AM
 */

#ifndef ISQLRESULT_HPP
#define	ISQLRESULT_HPP

/**
 * Interface returned by a SQL task which need to returns something
 */
class ISqlResult
{
public:

  virtual ~ISqlResult() { }

  /**
   * Returns true if any error occured
   */
  virtual bool error() const
  {
    return error_;
  }

  /**
   * (void *) pointing to something your sqltask created. be careful when casting.
   */
  virtual void *result()
  {
    return result_;
  };

  bool error_;
  void *result_;
  ;
};

#endif	/* ISQLRESULT_HPP */


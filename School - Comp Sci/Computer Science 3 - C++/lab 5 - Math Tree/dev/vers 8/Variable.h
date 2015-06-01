#ifndef VARIABLE_H
#define VARIABLE_H

class Variable
	{
	public:
		typedef	int			ValueType;
		enum	Exception	{
							VariableNotDefinedException
							};

							Variable		();
				explicit	Variable		(const Variable &);
							~Variable		();
		void				ClearDefined	();
		ValueType			GetValue		() const;
		bool				IsDefined		() const;
		bool				IsNotDefined	() const;
		void				SetDefined		();
		void				SetValue		(ValueType V);
		Variable &			operator =		(const Variable &);
	private:
		bool				Defined;
		ValueType			Value;
	};

inline Variable::Variable (): Value (0)
		{
		ClearDefined ();
		}

inline Variable::Variable (const Variable & V)
		{
		*this = V;
		}

inline Variable::~Variable ()
		{
		}

inline void Variable::ClearDefined ()
		{
		Defined = false;
		}

inline Variable::ValueType Variable::GetValue () const
		{
		if (IsDefined ())
				return Value;
			else
				throw VariableNotDefinedException;
		}

inline bool Variable::IsDefined () const
		{
		return Defined;
		}

inline bool Variable::IsNotDefined () const
		{
		return !Defined;
		}

inline void Variable::SetDefined ()
		{
		Defined = true;
		}

inline void Variable::SetValue (ValueType V)
		{
		SetDefined ();
		Value = V;
		}

inline Variable & Variable::operator = (const Variable & V)
		{
		if (this != &V)
				{
				Defined	= V.IsDefined ();
				Value	= V.Value;
				}
			else;
		return *this;
		}

#endif

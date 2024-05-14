﻿using System;
using System.Text.RegularExpressions;
using UnityEngine;

namespace TBydFramework.Runtime.Configuration
{
    public class DefaultTypeConverter : ITypeConverter
    {
        public virtual bool Support(Type type)
        {
#if NETFX_CORE
            TypeCode typeCode = WinRTLegacy.TypeExtensions.GetTypeCode(type);
#else
            TypeCode typeCode = Type.GetTypeCode(type);
#endif

            switch (typeCode)
            {
                case TypeCode.Boolean:
                case TypeCode.Char:
                case TypeCode.SByte:
                case TypeCode.Byte:
                case TypeCode.Int16:
                case TypeCode.UInt16:
                case TypeCode.Int32:
                case TypeCode.UInt32:
                case TypeCode.Int64:
                case TypeCode.UInt64:
                case TypeCode.Single:
                case TypeCode.Double:
                case TypeCode.DateTime:
                case TypeCode.String:
                case TypeCode.Decimal:
                    return true;
                default:
                    {
                        if (type.Equals(typeof(Version)))
                            return true;
                        if (type.Equals(typeof(Color)))
                            return true;
                        if (type.Equals(typeof(Vector2)))
                            return true;
                        if (type.Equals(typeof(Vector3)))
                            return true;
                        if (type.Equals(typeof(Vector4)))
                            return true;
                        if (type.Equals(typeof(Rect)))
                            return true;
                        return false;
                    }
            }
        }

        public virtual object Convert(Type type, object value)
        {
#if NETFX_CORE
            TypeCode typeCode = WinRTLegacy.TypeExtensions.GetTypeCode(type);
#else
            TypeCode typeCode = Type.GetTypeCode(type);
#endif

            switch (typeCode)
            {
                case TypeCode.Boolean:
                    if (value is string)
                    {
                        string v = ((string)value).Trim().ToLower();
                        if (v.Equals("yes") || v.Equals("true"))
                            return true;
                        else if (v.Equals("no") || v.Equals("false"))
                            return false;
                        else
                            throw new FormatException();
                    }
                    else
                    {
                        return System.Convert.ChangeType(value, type);
                    }
                case TypeCode.Char:
                case TypeCode.SByte:
                case TypeCode.Byte:
                case TypeCode.Int16:
                case TypeCode.UInt16:
                case TypeCode.Int32:
                case TypeCode.UInt32:
                case TypeCode.Int64:
                case TypeCode.UInt64:
                case TypeCode.Single:
                case TypeCode.Double:
                case TypeCode.DateTime:
                case TypeCode.String:
                case TypeCode.Decimal:
                    return System.Convert.ChangeType(value, type);
                default:
                    {
                        if (type.Equals(typeof(Version)))
                        {
                            if (value is Version)
                                return (Version)value;

                            if (!(value is string))
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name));

                            try
                            {
                                return new Version((string)value);
                            }
                            catch (Exception e)
                            {
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name), e);
                            }
                        }
                        else if (type.Equals(typeof(Color)))
                        {
                            if (value is Color)
                                return (Color)value;

                            if (!(value is string))
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name));

                            try
                            {
                                Color color;
                                if (ColorUtility.TryParseHtmlString((string)value, out color))
                                    return color;
                            }
                            catch (Exception e)
                            {
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name), e);
                            }
                        }
                        else if (type.Equals(typeof(Vector2)))
                        {
                            if (value is Vector2)
                                return (Vector2)value;

                            if (!(value is string))
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name));

                            try
                            {
                                var val = Regex.Replace(((string)value).Trim(), @"(^\()|(\)$)", "");
                                string[] s = val.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                                if (s.Length == 2)
                                    return new Vector2(float.Parse(s[0]), float.Parse(s[1]));
                            }
                            catch (Exception e)
                            {
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name), e);
                            }
                        }
                        else if (type.Equals(typeof(Vector3)))
                        {
                            if (value is Vector3)
                                return (Vector3)value;

                            if (!(value is string))
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name));

                            try
                            {
                                var val = Regex.Replace(((string)value).Trim(), @"(^\()|(\)$)", "");
                                string[] s = val.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                                if (s.Length == 3)
                                    return new Vector3(float.Parse(s[0]), float.Parse(s[1]), float.Parse(s[2]));
                            }
                            catch (Exception e)
                            {
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name), e);
                            }
                        }
                        else if (type.Equals(typeof(Vector4)))
                        {
                            if (value is Vector4)
                                return (Vector4)value;

                            if (!(value is string))
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name));

                            try
                            {
                                var val = Regex.Replace(((string)value).Trim(), @"(^\()|(\)$)", "");
                                string[] s = val.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                                if (s.Length == 4)
                                    return new Vector4(float.Parse(s[0]), float.Parse(s[1]), float.Parse(s[2]), float.Parse(s[3]));
                            }
                            catch (Exception e)
                            {
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name), e);
                            }
                        }
                        else if (type.Equals(typeof(Rect)))
                        {
                            if (value is Rect)
                                return (Rect)value;

                            if (!(value is string))
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name));

                            try
                            {
                                var val = Regex.Replace(((string)value).Trim(), @"(^\()|(\)$)", "");
                                string[] s = val.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                                if (s.Length == 4)
                                    return new Rect(float.Parse(s[0]), float.Parse(s[1]), float.Parse(s[2]), float.Parse(s[3]));
                            }
                            catch (Exception e)
                            {
                                throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name), e);
                            }
                        }

                        throw new FormatException(string.Format("This value \"{0}\" cannot be converted to the type \"{1}\"", value, type.Name));
                    }
            }
        }
    }
}

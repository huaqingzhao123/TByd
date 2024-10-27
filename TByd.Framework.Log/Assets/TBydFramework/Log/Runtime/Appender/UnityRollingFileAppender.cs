﻿using System.IO;
using UnityEngine;
using log4net.Appender;

namespace TBydFramework.Log.Runtime.Appender
{
    /// <summary>
    /// Unity滚动文件日志追加器,用于将日志写入滚动文件。
    /// </summary>
    public class UnityRollingFileAppender : RollingFileAppender
    {
        /// <summary>
        /// 设置日志文件的路径。
        /// </summary>
        public override string File
        {
            set
            {
                string path = Application.isEditor
                    ? Path.Combine(Directory.GetCurrentDirectory(), "Logs")
                    : Path.Combine(Application.temporaryCachePath, "Logs");

                base.File = Path.Combine(path, value); 
            }
        }
    }
}
﻿using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Threading.Tasks;
using TBydFramework.Runtime.Asynchronous;
using TBydFramework.Runtime.Log;
using UnityEngine;
using UnityEngine.Networking;

namespace TBydFramework.Runtime.Localizations
{
    /// <summary>
	/// AssetBundle data provider.
	/// dir:
	/// root/default/
	/// 
	/// root/zh/
	/// root/zh-CN/
	/// root/zh-TW/
	/// root/zh-HK/
	/// 
	/// root/en/
	/// root/en-US/
	/// root/en-CA/
	/// root/en-AU/
	/// </summary>
	public class AssetBundleDataProvider : IDataProvider
    {
        private static readonly ILog log = LogManager.GetLogger(typeof(AssetBundleDataProvider));

        private string assetBundleUrl;
        private IDocumentParser parser;

        public AssetBundleDataProvider(string assetBundleUrl) : this(assetBundleUrl, new XmlDocumentParser())
        {
        }

        public AssetBundleDataProvider(string assetBundleUrl, IDocumentParser parser)
        {
            if (string.IsNullOrEmpty(assetBundleUrl))
                throw new ArgumentNullException("assetBundleUrl");

            if (parser == null)
                throw new ArgumentNullException("parser");

            this.assetBundleUrl = assetBundleUrl;
            this.parser = parser;
        }

        public virtual async Task<Dictionary<string, object>> Load(CultureInfo cultureInfo)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            using (UnityWebRequest www = UnityWebRequestAssetBundle.GetAssetBundle(this.assetBundleUrl))
            {
                await www.SendWebRequest();

                DownloadHandlerAssetBundle handler = (DownloadHandlerAssetBundle)www.downloadHandler;
                AssetBundle bundle = handler.assetBundle;
                if (bundle == null)
                {
                    if (log.IsWarnEnabled)
                        log.WarnFormat("Failed to load Assetbundle from \"{0}\".", this.assetBundleUrl);
                    return dict;
                }
                try
                {
                    List<string> assetNames = new List<string>(bundle.GetAllAssetNames());
                    List<string> defaultPaths = assetNames.FindAll(p => p.Contains("/default/"));//eg:default
                    List<string> twoLetterISOpaths = assetNames.FindAll(p => p.Contains(string.Format("/{0}/", cultureInfo.TwoLetterISOLanguageName)));//eg:zh  en
                    List<string> paths = cultureInfo.Name.Equals(cultureInfo.TwoLetterISOLanguageName) ? null : assetNames.FindAll(p => p.Contains(string.Format("/{0}/", cultureInfo.Name)));//eg:zh-CN  en-US

                    FillData(dict, bundle, defaultPaths, cultureInfo);
                    FillData(dict, bundle, twoLetterISOpaths, cultureInfo);
                    FillData(dict, bundle, paths, cultureInfo);
                }
                finally
                {
                    try
                    {
                        if (bundle != null)
                            bundle.Unload(true);
                    }
                    catch (Exception) { }
                }
                return dict;
            }
        }

        private void FillData(Dictionary<string, object> dict, AssetBundle bundle, List<string> paths, CultureInfo cultureInfo)
        {
            try
            {
                if (paths == null || paths.Count <= 0)
                    return;

                foreach (string path in paths)
                {
                    try
                    {
                        TextAsset text = bundle.LoadAsset<TextAsset>(path);
                        using (MemoryStream stream = new MemoryStream(text.bytes))
                        {
                            var data = parser.Parse(stream, cultureInfo);
                            foreach (KeyValuePair<string, object> kv in data)
                            {
                                dict[kv.Key] = kv.Value;
                            }
                        }
                    }
                    catch (Exception e)
                    {
                        if (log.IsWarnEnabled)
                            log.WarnFormat("An error occurred when loading localized data from \"{0}\".Error:{1}", path, e);
                    }
                }
            }
            catch (Exception) { }
        }
    }
}

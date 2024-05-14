﻿using System;
using System.Collections.Generic;
using TBydFramework.Runtime.Asynchronous;
using UnityEngine;
using IAsyncResult = TBydFramework.Runtime.Asynchronous.IAsyncResult;

namespace TBydFramework.Runtime.Views
{
    [DisallowMultipleComponent]
    public class WindowContainer : Window, IWindowManager
    {
        public static WindowContainer Create(string name)
        {
            return Create(null, name);
        }

        public static WindowContainer Create(IWindowManager windowManager, string name)
        {
            GameObject root = new GameObject(name, typeof(CanvasGroup));
            RectTransform rectTransform = root.AddComponent<RectTransform>();
            rectTransform.anchorMin = Vector2.zero;
            rectTransform.anchorMax = Vector2.one;
            rectTransform.offsetMax = Vector2.zero;
            rectTransform.offsetMin = Vector2.zero;
            rectTransform.pivot = new Vector2(0.5f, 0.5f);
            rectTransform.localPosition = Vector3.zero;

            WindowContainer container = root.AddComponent<WindowContainer>();
            container.WindowManager = windowManager;
            container.Create();
            container.Show(true);
            return container;
        }

        private IWindowManager localWindowManager;

        protected override void OnCreate(IBundle bundle)
        {
            /* Create Window View */
            this.WindowType = WindowType.FULL;
            this.localWindowManager = this.CreateWindowManager();
        }

        protected virtual IWindowManager CreateWindowManager()
        {
            return this.gameObject.AddComponent<WindowManager>();
        }

        protected override void OnActivatedChanged()
        {
            if (this.localWindowManager != null)
                this.localWindowManager.Activated = this.Activated;
            base.OnActivatedChanged();
        }

        bool IWindowManager.Activated
        {
            get { return localWindowManager.Activated; }
            set { localWindowManager.Activated = value; }
        }

        public IWindow Current { get { return localWindowManager.Current; } }

        public int Count { get { return localWindowManager.Count; } }

        public override IAsyncResult Activate(bool ignoreAnimation)
        {
            if (!this.Visibility)
                throw new InvalidOperationException("The window is not visible.");

            if (this.localWindowManager.Current != null)
            {
                this.Activated = true;
                return (this.localWindowManager.Current as IManageable).Activate(ignoreAnimation);
            }

            AsyncResult result = new AsyncResult();
            try
            {
                if (this.Activated)
                {
                    result.SetResult();
                    return result;
                }

                if (!ignoreAnimation && this.ActivationAnimation != null)
                {
                    this.ActivationAnimation.OnStart(() =>
                    {
                        this.State = WindowState.ACTIVATION_ANIMATION_BEGIN;
                    }).OnEnd(() =>
                    {
                        this.State = WindowState.ACTIVATION_ANIMATION_END;
                        this.Activated = true;
                        this.State = WindowState.ACTIVATED;
                        result.SetResult();
                    }).Play();
                }
                else
                {
                    this.Activated = true;
                    this.State = WindowState.ACTIVATED;
                    result.SetResult();
                }
            }
            catch (Exception e)
            {
                result.SetException(e);
            }
            return result;
        }

        /// <summary>
        /// Passivate
        /// </summary>
        /// <returns></returns>
        public override IAsyncResult Passivate(bool ignoreAnimation)
        {
            if (!this.Visibility)
                throw new InvalidOperationException("The window is not visible.");

            if (this.localWindowManager.Current != null)
            {
                IAsyncResult currResult = (this.localWindowManager.Current as IManageable).Passivate(ignoreAnimation);
                currResult.Callbackable().OnCallback((r) =>
                {
                    this.Activated = false;
                });
                return currResult;
            }

            AsyncResult result = new AsyncResult();
            try
            {
                if (!this.Activated)
                {
                    result.SetResult();
                    return result;
                }

                this.Activated = false;
                this.State = WindowState.PASSIVATED;

                if (!ignoreAnimation && this.PassivationAnimation != null)
                {
                    this.PassivationAnimation.OnStart(() =>
                    {
                        this.State = WindowState.PASSIVATION_ANIMATION_BEGIN;
                    }).OnEnd(() =>
                    {
                        this.State = WindowState.PASSIVATION_ANIMATION_END;
                        result.SetResult();
                    }).Play();
                }
                else
                {
                    result.SetResult();
                }
            }
            catch (Exception e)
            {
                result.SetException(e);
            }
            return result;
        }

        public IEnumerator<IWindow> Visibles()
        {
            return localWindowManager.Visibles();
        }

        public IWindow Get(int index)
        {
            return localWindowManager.Get(index);
        }

        public void Add(IWindow window)
        {
            localWindowManager.Add(window);
        }

        public bool Remove(IWindow window)
        {
            return localWindowManager.Remove(window);
        }

        public IWindow RemoveAt(int index)
        {
            return localWindowManager.RemoveAt(index);
        }

        public bool Contains(IWindow window)
        {
            return localWindowManager.Contains(window);
        }

        public int IndexOf(IWindow window)
        {
            return localWindowManager.IndexOf(window);
        }

        public List<IWindow> Find(bool visible)
        {
            return localWindowManager.Find(visible);
        }

        public T Find<T>() where T : IWindow
        {
            return localWindowManager.Find<T>();
        }

        public T Find<T>(string name) where T : IWindow
        {
            return localWindowManager.Find<T>(name);
        }

        public List<T> FindAll<T>() where T : IWindow
        {
            return localWindowManager.FindAll<T>();
        }

        public void Clear()
        {
            localWindowManager.Clear();
        }

        public ITransition Show(IWindow window)
        {
            return localWindowManager.Show(window);
        }

        public ITransition Hide(IWindow window)
        {
            return localWindowManager.Hide(window);
        }

        public ITransition Dismiss(IWindow window)
        {
            return localWindowManager.Dismiss(window);
        }
    }
}

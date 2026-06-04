using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Newtonsoft.Json;

namespace DictionaryApp
{
    // Управление всеми словарями
    public class AppManager
    {
        private readonly string _dictionariesFolder = "Dictionaries";
        private Dictionary<string, DictionaryManager> _loadedDictionaries;

        public AppManager()
        {
            _loadedDictionaries = new Dictionary<string, DictionaryManager>();
            
            // Папку для словарей если её нет
            if (!Directory.Exists(_dictionariesFolder))
                Directory.CreateDirectory(_dictionariesFolder);
        }

        // Создание нового словаря
        public void CreateDictionary(string dictionaryName)
        {
            dictionaryName = dictionaryName.ToLower();
            
            if (_loadedDictionaries.ContainsKey(dictionaryName))
            {
                Console.WriteLine("Словарь с таким именем уже существует.");
                return;
            }

            string filePath = Path.Combine(_dictionariesFolder, $"{dictionaryName}.json");
            if (File.Exists(filePath))
            {
                Console.WriteLine("Файл словаря уже существует. Загружаем его.");
                var existingDict = new DictionaryManager(dictionaryName, _dictionariesFolder);
                _loadedDictionaries.Add(dictionaryName, existingDict);
                return;
            }

            var newDict = new DictionaryManager(dictionaryName, _dictionariesFolder);
            _loadedDictionaries.Add(dictionaryName, newDict);
            Console.WriteLine($"Словарь '{dictionaryName}' успешно создан.");
        }

        // Получение словаря по имени
        public DictionaryManager GetDictionary(string dictionaryName)
        {
            dictionaryName = dictionaryName.ToLower();
            
            if (_loadedDictionaries.TryGetValue(dictionaryName, out var dict))
                return dict;

            string filePath = Path.Combine(_dictionariesFolder, $"{dictionaryName}.json");
            if (File.Exists(filePath))
            {
                var loadedDict = new DictionaryManager(dictionaryName, _dictionariesFolder);
                _loadedDictionaries.Add(dictionaryName, loadedDict);
                return loadedDict;
            }

            return null;
        }

        // Вывод списка всех словарей
        public void ListDictionaries()
        {
            var files = Directory.GetFiles(_dictionariesFolder, "*.json");
            if (files.Length == 0)
            {
                Console.WriteLine("Нет доступных словарей.");
                return;
            }

            Console.WriteLine("Доступные словари:");
            foreach (var file in files)
            {
                string name = Path.GetFileNameWithoutExtension(file);
                Console.WriteLine($" - {name}");
            }
        }
    }

    // Управление одним словарём
    public class DictionaryManager
    {
        private string _name;
        private string _filePath;
        private Dictionary<string, List<string>> _words;

        public DictionaryManager(string name, string folderPath)
        {
            _name = name.ToLower();
            _filePath = Path.Combine(folderPath, $"{_name}.json");
            LoadFromFile();
        }

        // Добавление слова и его переводов
        public void AddWord(string word, List<string> translations)
        {
            word = word.ToLower().Trim();
            
            if (!_words.ContainsKey(word))
            {
                _words[word] = new List<string>();
            }

            foreach (var translation in translations)
            {
                string cleanTranslation = translation.ToLower().Trim();
                if (!_words[word].Contains(cleanTranslation))
                {
                    _words[word].Add(cleanTranslation);
                }
            }
            
            SaveToFile();
            Console.WriteLine($"Слово '{word}' успешно добавлено/обновлено.");
        }

        // Замена самого слова
        public void ReplaceWord(string oldWord, string newWord)
        {
            oldWord = oldWord.ToLower().Trim();
            newWord = newWord.ToLower().Trim();

            if (!_words.ContainsKey(oldWord))
            {
                Console.WriteLine($"Слово '{oldWord}' не найдено.");
                return;
            }

            if (oldWord == newWord)
            {
                Console.WriteLine("Старое и новое слово совпадают.");
                return;
            }

            var translations = _words[oldWord];
            _words.Remove(oldWord);
            
            if (!_words.ContainsKey(newWord))
            {
                _words[newWord] = translations;
            }
            else
            {
                foreach (var t in translations)
                {
                    if (!_words[newWord].Contains(t))
                        _words[newWord].Add(t);
                }
            }
            
            SaveToFile();
            Console.WriteLine($"Слово '{oldWord}' заменено на '{newWord}'.");
        }

        // Замена конкретного перевода у слова
        public void ReplaceTranslation(string word, string oldTranslation, string newTranslation)
        {
            word = word.ToLower().Trim();
            oldTranslation = oldTranslation.ToLower().Trim();
            newTranslation = newTranslation.ToLower().Trim();

            if (!_words.ContainsKey(word))
            {
                Console.WriteLine($"Слово '{word}' не найдено.");
                return;
            }

            var translations = _words[word];
            int index = translations.IndexOf(oldTranslation);
            if (index == -1)
            {
                Console.WriteLine($"Перевод '{oldTranslation}' не найден.");
                return;
            }

            if (translations.Contains(newTranslation) && oldTranslation != newTranslation)
            {
                Console.WriteLine($"Перевод '{newTranslation}' уже существует.");
                return;
            }

            translations[index] = newTranslation;
            SaveToFile();
            Console.WriteLine($"Перевод изменён.");
        }

        // Удаление слова целиком
        public void DeleteWord(string word)
        {
            word = word.ToLower().Trim();
            if (_words.Remove(word))
            {
                SaveToFile();
                Console.WriteLine($"Слово '{word}' удалено.");
            }
            else
            {
                Console.WriteLine($"Слово '{word}' не найдено.");
            }
        }

        // Удаление одного перевода
        public void DeleteTranslation(string word, string translation)
        {
            word = word.ToLower().Trim();
            translation = translation.ToLower().Trim();

            if (!_words.ContainsKey(word))
            {
                Console.WriteLine($"Слово '{word}' не найдено.");
                return;
            }

            var translations = _words[word];
            
            if (translations.Count <= 1)
            {
                Console.WriteLine("Ошибка: Нельзя удалить последний вариант перевода.");
                return;
            }

            if (translations.Remove(translation))
            {
                SaveToFile();
                Console.WriteLine($"Перевод '{translation}' удалён.");
            }
            else
            {
                Console.WriteLine($"Перевод '{translation}' не найден.");
            }
        }

        // Поиск слова
        public void SearchWord(string word)
        {
            word = word.ToLower().Trim();
            if (_words.TryGetValue(word, out var translations))
            {
                Console.WriteLine($"Слово: {word}");
                Console.WriteLine("Переводы:");
                foreach (var t in translations)
                    Console.WriteLine($"  - {t}");
            }
            else
            {
                Console.WriteLine($"Слово '{word}' не найдено в словаре '{_name}'.");
            }
        }

        // Экспорт слова в файл
        public void ExportWord(string word, string exportFolder = "Exports")
        {
            word = word.ToLower().Trim();
            if (!_words.TryGetValue(word, out var translations))
            {
                Console.WriteLine($"Слово '{word}' не найдено.");
                return;
            }

            if (!Directory.Exists(exportFolder))
                Directory.CreateDirectory(exportFolder);

            string content = $"Слово: {word}\nПереводы:\n";
            foreach (var t in translations)
                content += $"- {t}\n";

            string fileName = $"{_name}_{word}.txt";
            string filePath = Path.Combine(exportFolder, fileName);
            
            File.WriteAllText(filePath, content);
            Console.WriteLine($"Слово экспортировано в: {filePath}");
        }

        // Вывод всех слов на экран
        public void DisplayAllWords()
        {
            if (_words.Count == 0)
            {
                Console.WriteLine("Словарь пуст.");
                return;
            }

            Console.WriteLine($"Содержимое словаря '{_name}':");
            foreach (var pair in _words)
            {
                Console.WriteLine($"- {pair.Key}: {string.Join(", ", pair.Value)}");
            }
        }

        // Сохранение в JSON
        private void SaveToFile()
        {
            string json = JsonConvert.SerializeObject(_words, Formatting.Indented);
            File.WriteAllText(_filePath, json);
        }

        // Загрузка из JSON
        private void LoadFromFile()
        {
            if (File.Exists(_filePath))
            {
                string json = File.ReadAllText(_filePath);
                _words = JsonConvert.DeserializeObject<Dictionary<string, List<string>>>(json) 
                         ?? new Dictionary<string, List<string>>();
            }
            else
            {
                _words = new Dictionary<string, List<string>>();
            }
        }
    }

    // Меню и управление
    class Program
    {
        static AppManager appManager = new AppManager();
        static string currentDictionaryName = null;
        static DictionaryManager currentDict = null;

        static void Main(string[] args)
        {
            MainMenu();
        }

        // Главное меню
        static void MainMenu()
        {
            while (true)
            {
                Console.Clear();
                Console.WriteLine("1. Выбрать словарь");
                Console.WriteLine("2. Создать новый словарь");
                Console.WriteLine("3. Показать все словари");
                Console.WriteLine("0. Выход");
                Console.Write("Ваш выбор: ");

                string choice = Console.ReadLine();

                switch (choice)
                {
                    case "1": SelectDictionaryMenu(); break;
                    case "2": CreateDictionaryMenu(); break;
                    case "3":
                        appManager.ListDictionaries();
                        Console.WriteLine("\nНажмите любую клавишу");
                        Console.ReadKey();
                        break;
                    case "0": return;
                    default:
                        Console.WriteLine("Неверный выбор");
                        Console.ReadKey();
                        break;
                }
            }
        }

        // Выбор словаря
        static void SelectDictionaryMenu()
        {
            Console.Clear();
            Console.WriteLine("Выбор словаря");
            appManager.ListDictionaries();
            
            Console.Write("\nВведите имя словаря (0 - назад): ");
            string dictName = Console.ReadLine();
            if (dictName == "0") return;

            currentDict = appManager.GetDictionary(dictName);
            if (currentDict != null)
            {
                currentDictionaryName = dictName.ToLower();
                DictionaryMenu();
            }
            else
            {
                Console.WriteLine($"Словарь '{dictName}' не найден.");
                Console.ReadKey();
            }
        }

        // Создание словаря
        static void CreateDictionaryMenu()
        {
            Console.Clear();
            Console.Write("Введите тип словаря (англо-русский): ");
            string name = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(name))
            {
                appManager.CreateDictionary(name);
            }
            Console.ReadKey();
        }

        // Меню операций с выбранным словарём
        static void DictionaryMenu()
        {
            while (true)
            {
                Console.Clear();
                Console.WriteLine($"Словарь '{currentDictionaryName}'");
                Console.WriteLine("1. Показать все слова");
                Console.WriteLine("2. Добавить слово / перевод");
                Console.WriteLine("3. Заменить слово");
                Console.WriteLine("4. Заменить перевод");
                Console.WriteLine("5. Удалить слово");
                Console.WriteLine("6. Удалить перевод");
                Console.WriteLine("7. Найти перевод слова");
                Console.WriteLine("8. Экспортировать слово в файл");
                Console.WriteLine("0. Возврат в главное меню");
                Console.Write("Ваш выбор: ");

                string choice = Console.ReadLine();

                switch (choice)
                {
                    case "1": currentDict.DisplayAllWords(); Console.ReadKey(); break;
                    case "2": AddWordMenu(); break;
                    case "3": ReplaceWordMenu(); break;
                    case "4": ReplaceTranslationMenu(); break;
                    case "5": DeleteWordMenu(); break;
                    case "6": DeleteTranslationMenu(); break;
                    case "7": SearchWordMenu(); break;
                    case "8": ExportWordMenu(); break;
                    case "0": return;
                    default: Console.WriteLine("Неверный выбор"); Console.ReadKey(); break;
                }
            }
        }

        // Методы для ввода данных
        static void AddWordMenu()
        {
            Console.Write("Введите слово: ");
            string word = Console.ReadLine();
            Console.Write("Введите переводы через запятую: ");
            string input = Console.ReadLine();
            var translations = input.Split(',').Select(t => t.Trim()).Where(t => t != "").ToList();
            if (translations.Count > 0) currentDict.AddWord(word, translations);
            Console.ReadKey();
        }

        static void ReplaceWordMenu()
        {
            Console.Write("Старое слово: ");
            string oldW = Console.ReadLine();
            Console.Write("Новое слово: ");
            string newW = Console.ReadLine();
            currentDict.ReplaceWord(oldW, newW);
            Console.ReadKey();
        }

        static void ReplaceTranslationMenu()
        {
            Console.Write("Слово: ");
            string w = Console.ReadLine();
            Console.Write("Старый перевод: ");
            string oldT = Console.ReadLine();
            Console.Write("Новый перевод: ");
            string newT = Console.ReadLine();
            currentDict.ReplaceTranslation(w, oldT, newT);
            Console.ReadKey();
        }

        static void DeleteWordMenu()
        {
            Console.Write("Слово для удаления: ");
            currentDict.DeleteWord(Console.ReadLine());
            Console.ReadKey();
        }

        static void DeleteTranslationMenu()
        {
            Console.Write("Слово: ");
            string w = Console.ReadLine();
            Console.Write("Перевод для удаления: ");
            currentDict.DeleteTranslation(w, Console.ReadLine());
            Console.ReadKey();
        }

        static void SearchWordMenu()
        {
            Console.Write("Слово для поиска: ");
            currentDict.SearchWord(Console.ReadLine());
            Console.ReadKey();
        }

        static void ExportWordMenu()
        {
            Console.Write("Слово для экспорта: ");
            currentDict.ExportWord(Console.ReadLine());
            Console.ReadKey();
        }
    }
}
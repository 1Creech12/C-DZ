#!/usr/bin/env python3
import sys
import os
import argparse
import sqlite3

# Добавляем текущую папку в путь
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from ittopjournal import get_feedback_info


def parse_feedback(token: str, db_path: str):
    """Парсинг отзывов"""
    db = sqlite3.connect(db_path)
    c = db.cursor()

    c.execute('''
        CREATE TABLE IF NOT EXISTS feedback (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date TEXT NOT NULL, 
            message TEXT NOT NULL,
            full_spec TEXT NOT NULL,
            teacher TEXT NOT NULL
        )
    ''')

    c.execute("DELETE FROM feedback")

    try:
        feedback = get_feedback_info(token)

        if not feedback:
            print("Нет данных об отзывах")
            return

        for item in feedback:
            c.execute('''
                INSERT INTO feedback (date, message, full_spec, teacher)
                VALUES (?, ?, ?, ?)
            ''', (item.get("date", ""), item.get("message", ""), 
                  item.get("full_spec", ""), item.get("teacher", "")))

        db.commit()
        print(f"Отзывы: Добавлено {len(feedback)} записей")

    except Exception as e:
        print(f"Ошибка парсинга отзывов: {str(e)}")
        db.rollback()
        raise
    finally:
        db.close()


def main():
    parser = argparse.ArgumentParser(description='Парсер отзывов')
    parser.add_argument('--token', required=True, help='JWT токен авторизации')
    parser.add_argument('--db', required=True, help='Путь к файлу БД feedback.db')

    args = parser.parse_args()

    try:
        parse_feedback(args.token, args.db)
        sys.exit(0)
    except Exception as e:
        print(f"Критическая ошибка: {str(e)}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
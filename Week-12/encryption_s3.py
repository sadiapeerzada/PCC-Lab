"""Week 12, Problem 12.1: upload a file to S3 with server-side encryption.
Requires an existing S3 bucket, AWS permission and installed boto3.
Does NOT create, change or delete any bucket and does not make objects public.
"""
import argparse
from pathlib import Path
import boto3
from botocore.exceptions import BotoCoreError, ClientError, NoCredentialsError


def main():
    parser = argparse.ArgumentParser(description="S3 encrypted upload demo")
    parser.add_argument("bucket", help="Your existing S3 bucket")
    parser.add_argument("file", type=Path, help="Local file to upload")
    parser.add_argument("--key", help="S3 object key (default: file name)")
    args = parser.parse_args()
    if not args.file.is_file():
        parser.error("The source file does not exist")
    key = args.key or args.file.name
    s3 = boto3.client("s3")  # Uses your configured AWS credentials and region.
    try:
        # HTTPS is used by the official AWS SDK endpoint by default.
        s3.upload_file(str(args.file), args.bucket, key,
                       ExtraArgs={"ServerSideEncryption": "AES256"})
        info = s3.head_object(Bucket=args.bucket, Key=key)
        mode = info.get("ServerSideEncryption", "not reported")
        print(f"Uploaded: s3://{args.bucket}/{key}")
        print(f"Encryption at rest (object metadata): {mode}")
        print(f"Bytes stored: {info.get('ContentLength', '?')}")
        if mode != "AES256":
            raise RuntimeError("Expected SSE-S3 encryption was not reported")
    except (BotoCoreError, ClientError, NoCredentialsError) as exc:
        raise SystemExit(f"AWS error: {exc}") from exc

if __name__ == "__main__":
    main()
